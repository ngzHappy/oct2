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

    /*测试图片显示*/
    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        for (const auto & image_name:images_names) {
            window->insertImage(QImage(image_name))
                ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        }
    }
    /*测试柱状图*/
    window->insertHist({ 1,2,3,4,5 })->setWindowTitle(u8"柱状图"_qs);
    /*测试散点图*/
    auto scatter=window->insertScatter({ {0,0},{1,1},{2,2} });
    scatter->setCentrePointPaint(
        std::shared_ptr< std::function<void(QPainter *)> >(
        new std::function<void(QPainter *)>{
        [](QPainter * painter) {
        painter->setBrush(Qt::transparent);
        painter->setPen(QPen(QColor(0,0,0),1));
        painter->drawRect(QRect{-10,-10,20,20});
    }
    }
        )
        );
    scatter->setWindowTitle(u8"散点图"_qs);

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}
