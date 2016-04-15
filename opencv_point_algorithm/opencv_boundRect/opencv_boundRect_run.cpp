/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCharts>
#include "private/opencv_boundRect_run_exception.cpp"

static inline std::vector<cv::Point2f>
genRandPoint() {
    enum {SIZE=100};
    std::vector<cv::Point2f> ans;
    ans.reserve(SIZE);
    for (std::intptr_t i=0; i<SIZE;++i) {
        const double x_=std::sin(double(std::rand()))*0.707;
        const double y_=std::cos(double(std::rand()))*0.707;
        ans.emplace_back(
            static_cast<float>(x_+y_),
            static_cast<float>(x_-y_));
    }
    return std::move(ans);
}
namespace opencv_boundRect{
extern void run(OpenCVWindow * window) try{

    std::vector<cv::Point2f> points_input=
        genRandPoint();

    auto * item_ = window->insertScatter(points_input.begin(),points_input.end());
    item_->setWindowTitle(u8"矩形"_qs);

    cv::Rect rect = cv::boundingRect( points_input );
    std::cout<<rect<<std::endl;
    std::array<cv::Point2f,4> points_;
    points_[0]=rect.tl();
    points_[1]=cv::Point2f(points_[0].x+rect.width,points_[0].y);
    points_[2]=rect.br();
    points_[3]=cv::Point2f(points_[0].x,points_[0].y+rect.height);
    std::cout
        <<points_[0]<<std::endl
        <<points_[1]<<std::endl
        <<points_[2]<<std::endl
        <<points_[3]<<std::endl;

    /*绘制矩形*/
    QtCharts::QLineSeries * series_=new QtCharts::QLineSeries;
    series_->append({points_[0].x,points_[0].y});
    series_->append({points_[1].x,points_[1].y});
    series_->append({points_[2].x,points_[2].y});
    series_->append({points_[3].x,points_[3].y});
    series_->append({points_[0].x,points_[0].y});
    series_->setPen(QPen(QColor(0,0,0),2));
    series_->setPointsVisible(true);
    auto * chart_=item_->getChart();
    chart_->addSeries(series_);
    chart_->setAxisX(chart_->axisX(item_->getScatterSeries()),series_);
    chart_->setAxisY(chart_->axisY(item_->getScatterSeries()),series_);
    chart_->axisX(item_->getScatterSeries())
        ->setRange(-0.5+points_[0].x,0.5+points_[2].x);
    chart_->axisY(item_->getScatterSeries())
        ->setRange(-0.5+points_[0].y,0.5+points_[2].y);
}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}
}
