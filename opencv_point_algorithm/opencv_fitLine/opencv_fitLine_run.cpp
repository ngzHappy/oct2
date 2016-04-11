/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include <QtCharts>

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

extern void run(OpenCVWindow * window) try {

    std::vector<cv::Point2f> varPointsInput;

    varPointsInput=
        CoreUtility::getConfigurationFile()
        .getInputData2D<float,std::vector< cv::Point2f >/**/>();

    auto varItem = window->insertLineSeries(
        varPointsInput.begin(),
        varPointsInput.end()
        );

    varItem->setWindowTitle(u8"直线拟合"_qs);

    cv::Vec4f varAns;
    cv::fitLine(
        varPointsInput/*input*/,
        varAns/*output*/,
        cv::DIST_L2/*最小二乘法*/,
        0,
        0.01,
        0.01
        );

    std::cout
        <<"dx: "<<varAns[0]<<std::endl
        <<"dy: "<<varAns[1]<<std::endl
        <<"x0: "<<varAns[2]<<std::endl
        <<"y0: "<<varAns[3]<<std::endl;
    
    /*
    -dy*x+dx*y+c=0;
    c=dy*x0-dx*y0
    y=(dy*x-c)/dx
    */
    auto & varDx=varAns[0];
    auto & varDy=varAns[1];
    auto & varX0=varAns[2];
    auto & varY0=varAns[3];
    auto varY=
        [
            _varC=-((varDy*varX0)-(varDx*varY0)),
            _varDy=varDy,_varDx=1.0/varDx
        ](auto argX) {
        return (_varC+_varDy*argX)*_varDx;
    };

    if (varPointsInput.empty()) { return; }
    auto varFirstPointX=varPointsInput.front().x;
    auto varLastPointX=varPointsInput.rbegin()->x;
 
    auto varChart = varItem->getChart();
    auto varLineSeriex=new QtCharts::QLineSeries;
    varLineSeriex->append(varFirstPointX,varY(varFirstPointX));
    varLineSeriex->append(varLastPointX,varY(varLastPointX));
    varChart->addSeries(varLineSeriex);
    varChart->setAxisY(varChart->axisY(varItem->getLineSeries()),varLineSeriex);
    varChart->setAxisX(varChart->axisX(varItem->getLineSeries()),varLineSeriex);
    varLineSeriex->setPen(QPen(QColor(1,1,1),2));
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

