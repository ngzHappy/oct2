#include <string>
#include <sstream>
#include <memory>
#include <iostream>
#include <fstream>
#include <PartBoost.hpp>

using namespace std::literals;

extern void write_hpp(std::ostream & out,const std::string & class_name,const std::string & upper_class_name);
extern void write_data(std::ostream & out,const std::string & class_name,const std::string & upper_class_name);
extern void write_function(std::ostream & out,const std::string & class_name,const std::string & upper_class_name);
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

    using ofstream=boost::filesystem::ofstream;
    namespace filesystem=boost::filesystem;

    constexpr const char bom_[]{char(0xef),char(0xbb),char(0xbf)};
    if (argc==1) { return -1; }
    std::string className=argv[1];
    std::string outDirPath;

    if (argc>2) {
        outDirPath=argv[2];
    }
    else {
        outDirPath=filesystem::complete(
            filesystem::current_path()).string();
    }

    {
        if (outDirPath.size()<=0) { return -99; }
        if ( 
            (((*outDirPath.rbegin())!='/')&&
            ((*outDirPath.rbegin())!='\\')
            )) {
            outDirPath.push_back('/');
        }
    }

    std::string UClassName=className;
    for (auto &i:UClassName) {i=toUpper(i);}

    boost::filesystem::path path(outDirPath);
    if (false==filesystem::exists(path)) {
        filesystem::create_directories(path);
    }

    {
        std::string file_path_name=outDirPath+className+".hpp"s;
        std::ofstream ofs(file_path_name,std::ios::binary);
        ofs.write(bom_,3);
        write_hpp(ofs,className,UClassName);
    }
    
    path/="private"s;
    
    if (false==filesystem::exists(path)) {
        filesystem::create_directories(path);
    }
    
    {
        auto varPath=path/(className+"Data.hpp"s);
        ofstream ofs(varPath,std::ios::binary);
        ofs.write(bom_,3);
        write_data(ofs,className,UClassName);
    }

    {
        auto varPath=path/(className+"PrivateFunction.hpp"s);
        ofstream ofs(varPath,std::ios::binary);
        ofs.write(bom_,3);
        write_function(ofs,className,UClassName);
    }

    {
        std::ofstream ofs(outDirPath+className+".cpp"s,std::ios::binary);
        ofs.write(bom_,3);
        write_cpp(ofs,className,UClassName);
    }

    return 0;
}
