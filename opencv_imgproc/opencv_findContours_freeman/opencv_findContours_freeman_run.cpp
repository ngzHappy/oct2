/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include <QtCore/qdir.h>
//#include <QtCharts>

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

namespace {
inline constexpr int image_width() { return 512; }
inline constexpr int image_height() { return 512; }
inline constexpr int rect_width() { return 100; }
inline constexpr int rect_height() { return 60; }
inline constexpr double deg_to_rad(double _v_) { return _v_/180*3.141592654; }
QImage getTestImage(double angle/*deg*/) {
    QImage image_(image_width(),image_height(),QImage::Format_RGB32);
    image_.fill(QColor(0,0,0));
    QPainter painter_(&image_);
    painter_.translate(image_width()/2,image_height()/2);
    painter_.rotate(angle);
    painter_.setPen(QPen(QColor(255,255,255),1));
    painter_.setBrush(QColor(255,255,255));
    painter_.drawRect(QRectF(
        (-rect_width())/2,
        (-rect_height())/2,
        rect_width(),
        rect_height()
        ));
    return image_.convertToFormat(QImage::Format_Grayscale8);
}

}

extern void run(OpenCVWindow *  ) try{

    {
        QDir dir_(qApp->applicationDirPath());
        dir_.mkdir("freeman_test_images");
    }

    for (int deg=0; deg<360;++deg) {
        QImage image_=getTestImage(deg);
        image_.save(
            (qApp->applicationDirPath()+"/freeman_test_images/%1.png")
            .arg(deg,3,10,QChar('0'))
            );
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

