/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

extern void run(OpenCVWindow * window) {

    cv::Point2d point_0(1,2);
    cv::Point2d point_1(3,4);

    std::cout<<"point0 : "<<point_0<<std::endl;
    std::cout<<point_0.cross(point_1)<<std::endl;
    std::cout<<point_0.dot(point_1)<<std::endl;
    std::cout<<(point_0+point_1)<<std::endl;
    std::cout<<(point_0*2)<<std::endl;
    std::cout<<(point_0/2)<<std::endl;

    window->insertScatter({point_0,point_1});
}

