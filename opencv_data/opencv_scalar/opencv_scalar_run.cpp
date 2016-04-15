/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
#include <QtCore/qdebug.h>
#include "private/opencv_scalar_run_exception.cpp"

namespace opencv_scalar{
extern void run(OpenCVWindow *  ) try{

    cv::Scalar scalar(1,2,3,4);
    std::cout<<scalar<<std::endl;
    std::cout<<scalar.isReal()<<std::endl;
    std::cout<<cv::Scalar::all(1)<<std::endl;
}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}

}
