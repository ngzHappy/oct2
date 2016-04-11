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
    cv::Error::Code estatus=static_cast<cv::Error::Code>(status);
    (void)estatus;
#endif

    {
        QTextStream stream_(&__error_);
        stream_
            <<"function name:"<<func_name<<endl
            <<"error message:"<<err_msg<<endl
            <<"file name:"<<file_name<<endl
            <<"line:"<<line<<endl;
    }

    if (qApp) {
        qDebug().noquote()<<__error_;
        QErrorMessage errorBox;
        errorBox.setModal(true);
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

extern void run(OpenCVWindow *  ) try{

    cv::Scalar scalar(1,2,3,4);
    std::cout<<scalar<<std::endl;
    std::cout<<scalar.isReal()<<std::endl;
    std::cout<<cv::Scalar::all(1)<<std::endl;
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}
