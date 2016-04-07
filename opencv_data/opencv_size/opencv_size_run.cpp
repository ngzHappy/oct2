/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

extern void run(OpenCVWindow * ) {

    cv::Size2d size(100,200);
    std::cout<<size<<std::endl;
    std::cout<<size.area()<<std::endl;
    
}

