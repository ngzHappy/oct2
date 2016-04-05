/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <iostream>

extern void run(OpenCVWindow * ) {

    cv::Mat matrix(100,1,CV_32FC1);
    {
        intptr_t count_=0;
        matrix.forEach<std::float_t>([&count_](
            std::float_t &value,
            const int * const
            ) {
            value=++count_;
        });
    }

    std::cout<<matrix<<std::endl;
    
}

