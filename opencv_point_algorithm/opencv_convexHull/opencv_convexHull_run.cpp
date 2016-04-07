/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

namespace {

inline double pi_() { static double pi__=std::atan(1.0)*4;return pi__;}

inline double pi2_() {static double pi_2_=pi_()*2;return pi_2_;}

constexpr inline float to_float(long double v) { return static_cast<float>(v); }

inline std::vector<cv::Point2f>
genRandPoint() {
    enum {SIZE=500};
    static const double half_pi_=pi_()/2;
    static const double step_=pi2_()/6;
    const std::vector<cv::Point2f> test_data_{
        {std::sin(to_float(half_pi_)),std::cos(to_float(half_pi_))},
        {std::sin(to_float(half_pi_+step_)),std::cos(to_float(half_pi_+step_))},
        {std::sin(to_float(half_pi_+step_*2)),std::cos(to_float(half_pi_+step_*2))},
        {std::sin(to_float(half_pi_+step_*3)),std::cos(to_float(half_pi_+step_*3))},
        {std::sin(to_float(half_pi_+step_*4)),std::cos(to_float(half_pi_+step_*4))},
        {std::sin(to_float(half_pi_+step_*5)),std::cos(to_float(half_pi_+step_*5))},
    };

    std::vector<cv::Point2f> ans;
    for (std::intptr_t i=0; i<SIZE; ++i) {
    rand_begin_:
        const double x_=std::sin(double(std::rand())) ;
        const double y_=std::cos(double(std::rand())) ;
        auto aPoint = 
            cv::Point2f(static_cast<float>(x_),static_cast<float>(y_));
        if (cv::pointPolygonTest(test_data_,aPoint,false)<0) {
            goto rand_begin_;
        }
        ans.emplace_back(aPoint.x,aPoint.y);
    }
    return std::move(ans);

}

}

extern void run(OpenCVWindow * window) {

    std::vector<cv::Point2f> points_input=
        genRandPoint();

    auto * item_=window->insertScatter(points_input.begin(),points_input.end());
    item_->setWindowTitle(u8"凸包"_qs);

    std::vector<cv::Point2f> ans;
    cv::convexHull(points_input,ans);

    /*绘制凸包*/
    QtCharts::QLineSeries * series_=new QtCharts::QLineSeries;
    for (const auto & i:ans) {
        series_->append(i.x,i.y);
    }
    series_->append(ans[0].x,ans[0].y);
    series_->setPen(QPen(QColor(0,0,0),1));
    auto * chart_=item_->getChart();
    chart_->addSeries(series_);
    chart_->setAxisX(chart_->axisX(item_->getScatterSeries()),series_);
    chart_->setAxisY(chart_->axisY(item_->getScatterSeries()),series_);
    series_->setPointsVisible(true);
}

