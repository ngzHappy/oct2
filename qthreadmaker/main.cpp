#include <stdexcept>
#include <iostream>
extern int run(int argc,char ** argv);

int main(int argc,char ** argv) try{
    return run(argc,argv);
}
catch (const std::exception & e) {
    std::cout<<e.what()<<std::endl;
    return -1;
}
catch (...) {
    std::cout<<"???"<<std::endl;
    return -9999;
}



