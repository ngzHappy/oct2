/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
//#include <QtCharts>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
#include <OpenCVException.hpp>
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

extern void run(OpenCVWindow * window ) try{
   
    /*图片显示*/
    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("");

        for (const auto & image_name:images_names) {
            if (image_name.isEmpty()) { continue; }
            auto * item=window->insertChartImage(QImage(image_name));
            item->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
            item->setGridLineVisible(false,false);
        }
    }
    
    /*2d数据显示*/
    {
        auto points_2d=
        CoreUtility::getConfigurationFile().
            getInputData2D<qreal,QList<QPointF>>();
        if (points_2d.isEmpty()==false) {
            auto * item=window->insertScatter(points_2d);
            item->setWindowTitle(u8"散点图"_qs);
        }
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

