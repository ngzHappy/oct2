
/*
 * subdirs pro filepath
 * dir filepath
 * projectname
 *
 * example "c:/OpenCVTestNew.pro" "" "test"
 *
*/

#include <iostream>
#include <string>
#include <memory>
#include "ArgvPack.hpp"
extern int run( ArgvPack pack );

int main(int argc, char *argv[])try
{
    if(argc<4){
        /*输出帮助*/
        std::cout << "you should input :" <<std::endl;
        std::cout << "subdirs pro filepath"<<std::endl;
        std::cout << "dir path"<<std::endl;
        std::cout << "project name"<<std::endl;
        std::cout << "example : "
                  <<  "\"c:/OpenCVTestNew.pro\" \"\" \"test\""
                  << std::endl;
        return -1;
    }

    return run(argv);
}
catch (...) {
    std::cout<<"unknow exception @ main"<<std::endl;
    return -99999;
}


