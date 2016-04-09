/*run.cpp*/
#include <QtCharts>
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

namespace {

inline double pi_() {
    static double pi__=std::atan(1.0)*4;
    return pi__;
}

inline double pi2_() {
    static double pi_2_=pi_()*2;
    return pi_2_;
}

constexpr inline float to_float(long double v) { return static_cast<float>(v); }

inline std::vector<cv::Point2f>
genRandPoint() {

    static const double half_pi_=pi_()/2;
    static const double step_=pi2_()/6;
    static const std::vector<cv::Point2f> test_data_{
        {(to_float(half_pi_)),to_float(std::pow(half_pi_,2))},
        {(to_float(half_pi_+0.03)),to_float(std::pow(half_pi_+0.03,2))},
        {(to_float(half_pi_+step_)),to_float(std::pow(half_pi_+step_,2))},
        {(to_float(half_pi_+step_*2)),to_float(std::pow(half_pi_+step_*2,2))},
        {(to_float(half_pi_+step_*3)),to_float(std::pow(half_pi_+step_*3,2))},
        {(to_float(half_pi_+step_*4)),to_float(std::pow(half_pi_+step_*4,2))},
        {(to_float(half_pi_+step_*4+0.3)),to_float(std::pow(half_pi_+step_*4+0.3,2))},
        {(to_float(half_pi_+step_*5)),to_float(std::pow(half_pi_+step_*5,2))},
    };

    return test_data_;
}

}

extern void run(OpenCVWindow * window) try{

    std::vector<cv::Point2f> points_input=
        genRandPoint();

    auto * item_=window->insertScatter(points_input.begin(),points_input.end());
    item_->setWindowTitle(u8"曲线化直线"_qs);

    std::vector<cv::Point2f> ans;
    cv::approxPolyDP(points_input,ans,0.01,false);

    std::cout<<points_input.size()<<std::endl;
    std::cout<<ans.size()<<std::endl;

    /*绘制曲线*/
    QtCharts::QLineSeries * series_=new QtCharts::QLineSeries;
    for (const auto & i:ans) {
        series_->append(i.x,i.y);
    }
    series_->setPen(QPen(QColor(0,0,0),1));
    auto * chart_=item_->getChart();
    chart_->addSeries(series_);
    chart_->setAxisX(chart_->axisX(item_->getScatterSeries()),series_);
    chart_->setAxisY(chart_->axisY(item_->getScatterSeries()),series_);
    item_->getScatterSeries()->setPen(QPen(QColor(255,255,255),1));
    series_->setPointsVisible(true);

}
catch (const cv::Exception &) {
    /*std::quick_exit(-1);*/
}

/*
http://blog.csdn.net/wangqinghao/article/details/8207070
Douglas-Peucker算法（该算法名字够吓人，其实思想很简单）
在数字化时，要对曲线进行采样，即在曲线上取有限个点，将其变为折线，并且能够在一定程度
上保持原有的形状。
经典的Douglas-Peucker算法步骤如下：
（1）在曲线首尾两点A，B之间连接一条直线AB，该直线为曲线的弦；
（2）得到曲线上离该直线段距离最大的点C，计算其与AB的距离d；
（3）比较该距离与预先给定的阈值threshold的大小，如果小于threshold，则该直线段作为曲线的近似，该段曲线处理完毕。
（4）如果距离大于阈值，则用C将曲线分为两段AC和BC，并分别对两段取信进行1~3的处理。
（5）当所有曲线都处理完毕时，依次连接各个分割点形成的折线，即可以作为曲线的近似。
*/
