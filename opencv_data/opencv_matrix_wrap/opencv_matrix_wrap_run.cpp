/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <OpenCVMatProxyAllocator.hpp>
#include <vector>
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

extern void run(OpenCVWindow *) try{

    std::shared_ptr< std::vector<double> > 
        data_(new std::vector<double>{ 1,2,3,4,5 });
    cv::Mat matrix_(data_->size(),1,CV_64FC1,data_->data(),0);
    matrix_.u=OpenCVUserDataAllocator::instance()->allocate(
        new auto(data_),
        [](void * d_) { 
        std::cout<<"delete test data"<<std::endl;
        delete reinterpret_cast<
        std::shared_ptr< std::vector<double> > *>(d_); }
        );
     
    std::cout<<matrix_<<std::endl;

}
catch (const cv::Exception &) {
    /*std::quick_exit(-1);*/
}
