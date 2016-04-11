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

extern void run(OpenCVWindow * window) try{

    intptr_t count_=0;
    /*从配置文件中获得输入图片文件名*/
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");
    /*进行变换*/
    for (const auto & image_name:images_names) {
        ++count_;
        cv::Mat mat=OpenCVUtility::tryRead(QImage(image_name));
        window->insertImage(OpenCVUtility::tryRead(mat) )
            ->setWindowTitle(u8"第%1幅原始图片"_qs.arg(count_));
        cv::Mat ans;
        cv::blur(mat,ans,{3,3});/*平滑滤波*/
        cv::Canny(ans,ans,100,200);/*canny 边缘检测*/
        window->insertImage(OpenCVUtility::tryRead(ans) )
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}
