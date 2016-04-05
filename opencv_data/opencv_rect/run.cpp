/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

extern void run(OpenCVWindow * ) {

    cv::Rect2d rect(0,0,100,100);
    cv::Point2d point_0(0,0);
    cv::Point2d point_1(100,100);

    std::cout<<rect<<std::endl;
    std::cout<<std::boolalpha<<rect.contains(point_0)<<std::endl;
    std::cout<<std::boolalpha<<point_1.inside(rect)<<std::endl;
    std::cout<<rect.br()<<std::endl;
    std::cout<<rect.tl()<<std::endl;
    std::cout<<rect.area()<<std::endl;


}

