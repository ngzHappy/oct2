/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
#include <QtCore/qdebug.h>
namespace {
int ErrorCallback(
    int status/*cv::Error::Code*/,
    const char* func_name,
    const char* err_msg,
    const char* file_name,
    int line,
    void* /*userdata*/) {
    QString __error_;

#if !defined(NDEBUG)
    cv::Error::Code estatus= static_cast<cv::Error::Code>(status);
    (void)estatus;
#endif

    {
        QTextStream stream_(&__error_);
        stream_
            <<"function name:"<<func_name
            <<"error message:"<<err_msg
            <<"file name:"<<file_name
            <<"line:"<<line;
    }

    if (qApp) {
        QErrorMessage errorBox;
        errorBox.showMessage(__error_,"error");
        errorBox.exec();
    }
    else {
        qDebug().noquote()<<__error_;
    }

    return 0;
    (void)status;
}
}
/*当qapplication运行时注册此函数*/
static void _set_opencv_error_on_qt_start_up() {
    cv::redirectError(&ErrorCallback);
}
Q_COREAPP_STARTUP_FUNCTION(_set_opencv_error_on_qt_start_up)

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
    opencv_exception::error(e);
}
