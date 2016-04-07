/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <iostream>

extern void run(OpenCVWindow * ) {

    cv::Mat matrix(100,1,CV_32FC1);
    {
        intptr_t count_=0;
        for( auto pos=matrix.begin<float>();
             pos!=matrix.end<float>();
             ++pos){
            *pos=++count_;
        }
    }

    std::cout<<matrix<<std::endl;

}

