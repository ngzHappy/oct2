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

inline std::vector<cv::Point2f>
genRandPoint() {
    enum { SIZE=100 };
    std::vector<cv::Point2f> ans;
    ans.reserve(SIZE);
    const std::vector<cv::Point2f> test_triangle{
        {-1,-1},{1,-1},{0,1}
    };
    for (std::intptr_t i=0; i<SIZE; ++i) {
        rand_begin_:
        const double x_=std::sin(double(std::rand()))*0.707;
        const double y_=std::cos(double(std::rand()))*0.707;
        cv::Point2f a_point_(
            static_cast<float>(x_+y_),
            static_cast<float>(x_-y_));
        if (cv::pointPolygonTest(
            test_triangle,
            a_point_,false)<0) {
            goto rand_begin_;
        }
        ans.emplace_back(a_point_.x,a_point_.y);
    }
    return std::move(ans);
}

}

extern void run(OpenCVWindow * window) try{

    std::vector<cv::Point2f> points_input=
        genRandPoint();

    auto * item_ = window->insertScatter(points_input.begin(),points_input.end());
    item_->setWindowTitle(u8"外接三角形"_qs);

    std::vector<cv::Point2f> ans_(3);
    cv::minEnclosingTriangle(
        points_input,
        ans_
        );

    for (const auto & i:ans_) {
        std::cout<<i<<std::endl;
    }

    /*绘制外接三角形*/
    QtCharts::QLineSeries * series_=new QtCharts::QLineSeries;
    series_->append({ans_[0].x,ans_[0].y});
    series_->append({ans_[1].x,ans_[1].y});
    series_->append({ans_[2].x,ans_[2].y});
    series_->append({ans_[0].x,ans_[0].y});
    series_->setPen(QPen(QColor(0,0,0),2));
    series_->setPointsVisible(true);
    auto * chart_=item_->getChart();
    chart_->addSeries(series_);
    chart_->setAxisX(chart_->axisX(item_->getScatterSeries()),series_);
    chart_->setAxisY(chart_->axisY(item_->getScatterSeries()),series_);

}
catch (const cv::Exception &) {
    /*std::quick_exit(-1);*/
}
