﻿#include <string>
#include <sstream>
#include <memory>
#include <iostream>
#include <fstream>


using namespace std::literals;

extern void write_hpp(std::ostream & out,const std::string & class_name,const std::string & upper_class_name);
extern void write_cpp(std::ostream & out,const std::string & class_name,const std::string & upper_class_name);

namespace {
char toUpper(char i) {
    if (i>='a') {
        if (i<='z') {
            i-='a'; i+='A';
        }
    }
    return i;
}
}

int run(int argc,char ** argv) {
 
    constexpr const char bom_[]{char(0xef),char(0xbb),char(0xbf)};
    if (argc==1) { return -1; }
    std::string className=argv[1];
    std::string outDirPath;

    if (argc>2) {
        outDirPath=argv[2];
    }
   
    {
        if (outDirPath.size()>0) {
            if (
                (((*outDirPath.rbegin())!='/')&&
                    ((*outDirPath.rbegin())!='\\')
                )) {
                outDirPath.push_back('/');
            }
        }
    }

    std::string UClassName=className;
    for (auto &i:UClassName) {i=toUpper(i);}

    {
        std::string file_path_name=outDirPath+className+".hpp"s;
        std::ofstream ofs(file_path_name,std::ios::binary);
        ofs.write(bom_,3);
        write_hpp(ofs,className,UClassName);
    }
    
    {
        std::ofstream ofs(outDirPath+className+".cpp"s,std::ios::binary);
        ofs.write(bom_,3);
        write_cpp(ofs,className,UClassName);
    }

    return 0;
}
