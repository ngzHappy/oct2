/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

extern void run(OpenCVWindow *  ) {

    cv::Scalar scalar(1,2,3,4);
    std::cout<<scalar<<std::endl;
    std::cout<<scalar.isReal()<<std::endl;
    std::cout<<cv::Scalar::all(1)<<std::endl;
}

