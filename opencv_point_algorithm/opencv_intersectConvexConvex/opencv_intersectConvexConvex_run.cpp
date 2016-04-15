/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_intersectConvexConvex_run_exception.cpp"
#include <QtCharts>

namespace  {

std::pair<
std::vector<cv::Point2f>,
std::vector<cv::Point2f>
> gen_data(){

    std::pair<
    std::vector<cv::Point2f>,
    std::vector<cv::Point2f>
    >  ans;

    enum:std::int32_t{SIZE_=100};

    const double step_=CV_2PI/SIZE_;
    double value=0;
    for(std::int32_t i=0;i<SIZE_;++i){
        double x_=std::sin(value)/2;
        double y_=std::cos(value);
        value+=step_;
        ans.first.emplace_back(float(x_),float(y_));
        x_+=0.5;
        ans.second.emplace_back(float(x_),float(y_));
    }

    return std::move(ans);
}

}

namespace opencv_intersectConvexConvex{
extern void run(OpenCVWindow * window) try{

    auto data_ = gen_data();
    std::vector<cv::Point2f> ans;
    cv::intersectConvexConvex(data_.first,data_.second,ans);

    data_.first.push_back(*(data_.first.begin()));
    auto * item = window->insertLineSeries(data_.first.begin(),data_.first.end());

    QtCharts::QLineSeries * line1=[](auto & data) {
        auto ans = std::make_unique<QtCharts::QLineSeries>();
        data.push_back(*(data.begin()));
        for (const auto & i:data) {
            ans->append(i.x,i.y);
        }
        return ans.release();
    }(data_.second);
    item->getChart()->addSeries(line1);

    QtCharts::QLineSeries * line2=[](auto & data) {
        auto ans = std::make_unique<QtCharts::QLineSeries>();
        data.push_back(*(data.begin()));
        for (const auto & i:data) {
            ans->append(i.x,i.y);
        }
        return ans.release();
    }(ans);
    item->getChart()->addSeries(line2);

    auto * chart_=item->getChart();
    chart_->setAxisX(chart_->axisX(item->getLineSeries()),line2);
    chart_->setAxisX(chart_->axisX(item->getLineSeries()),line1);
    chart_->setAxisY(chart_->axisY(item->getLineSeries()),line2);
    chart_->setAxisY(chart_->axisY(item->getLineSeries()),line1);
    chart_->axisX()->setRange(-0.75,1.1);

    line1->setPen(QPen(QColor(200,100,200),2));
    line2->setPen(QPen(QColor(100,200,200),2));
    line1->setPointsVisible(true);
    item->setWindowTitle(u8"边界线交集"_qs);
}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

