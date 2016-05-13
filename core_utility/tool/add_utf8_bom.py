import os
import sys
import codecs
import os.path

def add_utf8_bom(fileName):
    with open(fileName,"r") as fr:
        lines = fr.readlines();
        if len(lines)>0:
            line_0=lines[0];
            if line_0.startswith(codecs.BOM_UTF8):
                return;
            if line_0.startswith(codecs.BOM_UTF16_BE):
                return;
            if line_0.startswith(codecs.BOM_UTF16_LE):
                return;
            if line_0.startswith(codecs.BOM_UTF32_BE):
                return;
            if line_0.startswith(codecs.BOM_UTF32_LE):
                return;
        else:
            return

        with open(fileName,"w") as fw:
            fw.write(codecs.BOM_UTF8);
            fw.writelines(lines);

def add_utf8_bom_dir(dirName):
    count=0;
    do_ext_name={".cpp",".h",".hpp",".c"}
    for parent,dirnames,filenames in os.walk(dirName):

        for fileName in filenames:
            extName=os.path.splitext(fileName);
            if len(extName)<=1:
                return;
            extName=extName[-1].lower()
            
            if extName in do_ext_name:
                fullPath=os.path.join(parent,fileName);
                count+=1;
                add_utf8_bom(fullPath);
    print("cout:"+str(count))
 

if __name__=="__main__":
    if len(sys.argv)>1:
        add_utf8_bom_dir(sys.argv[1]);
    else:
        add_utf8_bom_dir(os.getcwd());
    pass


