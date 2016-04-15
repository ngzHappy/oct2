const char *_run_exception_cpp=u8R"=_____=(/*run_exception.cpp*/
/*run_exception.cpp*/
#if !defined(PROJECT__RUN__EXCEPTION__OPENCV__CCT)
#define PROJECT__RUN__EXCEPTION__OPENCV__CCT

/*the file is just in this.run*/
#include <sstream>
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

#if defined(PROJECT__RUN__EXCEPTION__OPENCV__CCT_NEED)

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
#else
    (void)func_name;
    (void)err_msg;
    (void)line;
    (void)file_name;
#endif

    return 0;
    (void)status;
}

}

/*当qapplication运行时注册此函数*/
static void _set_opencv_error_on_qt_start_up() {
    cv::redirectError(&ErrorCallback);
}
Q_COREAPP_STARTUP_FUNCTION(_set_opencv_error_on_qt_start_up)

#endif



)=_____=";

