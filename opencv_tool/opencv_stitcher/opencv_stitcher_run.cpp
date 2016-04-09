/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <opencv2/stitching.hpp>
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
    std::vector< cv::Mat > images_;
    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        for (const auto & image_name:images_names) {
            QImage image_(image_name);
            window->insertImage(image_)
                ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
            images_.push_back(OpenCVUtility::tryRead(image_));
        }
    }
    auto stitcher=cv::createStitcher(true/*try_use_gpu*/);
    cv::Mat ans;
    stitcher->stitch(images_,ans);

    auto * item=window->insertChartImage(OpenCVUtility::tryRead(std::move(ans)));
    item->setWindowTitle(u8"全景图"_qs);
    item->setGridLineVisible(false,false);
}
catch (const cv::Exception &) {
    /*std::quick_exit(-1);*/
}
