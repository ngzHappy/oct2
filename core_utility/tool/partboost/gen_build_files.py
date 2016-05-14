
import os
import sys
import time
import shutil

def gen_filenames(rootPath):

    do_header_ext_name={".h",".hpp"}
    do_source_ext_name={".cpp",".c"}
    ansFileNames=[];
    for parent,dirnames,filenames in os.walk(rootPath):

        for fileName in filenames:
            extName=os.path.splitext(fileName);
            if len(extName)<=1:
                continue;
            extName=extName[-1].lower()
            
            if extName in do_header_ext_name:
                ansFileNames.append((parent,fileName,0))
            elif extName in do_source_ext_name:
                if fileName.find("test")>=0:
                    continue;
                if fileName.find("config_info")>=0:
                    continue;
                ansFileNames.append((parent,fileName,1))
            else:
                pass


    return ansFileNames


def copy_file_source(fromFileName,toFileName):
#BOOST_CHRONO_SOURCE
#BOOST_FILESYSTEM_SOURCE
#BOOST_REGEX_SOURCE
#BOOST_SYSTEM_SOURCE
    ##replace MACRO ##
    replace_data=(
        ("#define BOOST_CHRONO_SOURCE","#ifndef BOOST_CHRONO_SOURCE\n#define BOOST_CHRONO_SOURCE\n#endif/**/\n"),
        ("#define BOOST_FILESYSTEM_SOURCE","#ifndef BOOST_FILESYSTEM_SOURCE\n#define BOOST_FILESYSTEM_SOURCE\n#endif/**/\n"),
        ("#define BOOST_REGEX_SOURCE","#ifndef BOOST_REGEX_SOURCE\n#define BOOST_REGEX_SOURCE\n#endif/**/\n"),
        ("#define BOOST_SYSTEM_SOURCE","#ifndef BOOST_SYSTEM_SOURCE\n#define BOOST_SYSTEM_SOURCE\n#endif/**/\n"),
    );

    with open(fromFileName,"r") as source_file:
        with open(toFileName,"w") as target_file:
            source=source_file.read();
            for i_replace in replace_data:
                source=source.replace(i_replace[0],i_replace[1])
                pass
            target_file.write(source)
    pass

def copy_file_header(fromFileName,toFileName):
    shutil.copy2(fromFileName,toFileName)
    pass

def gen_build_files(rootPath):

    fileNames=gen_filenames(os.path.join(rootPath,"libs"))

    if len(fileNames)<1:
        return

    out_dir_path=os.path.join(rootPath,"outs")
    if os.path.exists(out_dir_path):
        shutil.rmtree(out_dir_path)

    ##wait for remove finished##
    time.sleep(0.1) 
    ####
    os.mkdir(out_dir_path);

    for fileName in fileNames:
        if fileName[2]:#if this is a cpp file
            souce_file_name=os.path.join(fileName[0],fileName[1])
            out_file_name=os.path.join(out_dir_path,"boost_"+fileName[1])#add boost_ for cpp files
            copy_file_source(souce_file_name,out_file_name)
        else:#if this is a hpp file
            souce_file_name=os.path.join(fileName[0],fileName[1])
            out_file_name=os.path.join(out_dir_path,fileName[1])
            copy_file_header(souce_file_name,out_file_name)
        pass

    pass

if __name__=="__main__":
    if len(sys.argv)>1:
        gen_build_files(sys.argv[1])
    else:
        gen_build_files(os.getcwd())


