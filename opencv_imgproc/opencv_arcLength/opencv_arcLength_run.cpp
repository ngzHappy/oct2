/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
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

    /*测试图片显示*/
    {

        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        QList<qreal> varContoursArea;

        for (const auto & image_name:images_names) {
            std::vector<std::vector<cv::Point>> varContoursPoints;
            {
                QImage varInputImage(image_name);
                cv::Mat varInputImageMat=
                    OpenCVUtility::tryRead(varInputImage);
                cv::findContours(
                    varInputImageMat,
                    varContoursPoints,
                    cv::RETR_EXTERNAL,
                    cv::CHAIN_APPROX_SIMPLE);
            }
            assert( varContoursPoints.empty()==false );
            cv::approxPolyDP(varContoursPoints[0],varContoursPoints[0],5,true);
            auto varAns = cv::arcLength(varContoursPoints[0],true) ;
            std::cout<<varAns<<",";
            varContoursArea.push_back(varAns);
        }

        if (false==varContoursArea.isEmpty()) {
            for (auto & vari:varContoursArea) {
                vari-=320;
                vari/=320;
                vari*=320;
            }
            window->insertHist(std::move(varContoursArea))
                ->setWindowTitle(u8"(检测值-320)/320的百分比"_qs);
        }
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

