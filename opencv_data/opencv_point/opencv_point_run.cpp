/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
#include <QtCore/qdebug.h>
#include "private/opencv_point_run_exception.cpp"

namespace opencv_point{
extern void run(OpenCVWindow * window) try{

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
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}

}
