/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
#include <QtCore/qdebug.h>
#include "private/opencv_size_run_exception.cpp"

namespace opencv_size{
extern void run(OpenCVWindow * ) try{

    cv::Size2d size(100,200);
    std::cout<<size<<std::endl;
    std::cout<<size.area()<<std::endl;

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}
