#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <vector>
#include <array>
#include <QtCharts>
#include "private/opencv_minEnclosingCircle_run_exception.cpp"

namespace {
inline std::vector<cv::Point2f>
genRandPoint() {
    enum { SIZE=100 };
    std::vector<cv::Point2f> ans;
    ans.reserve(SIZE);
    for (std::intptr_t i=0; i<SIZE; ++i) {
        const double x_=std::sin(double(std::rand()))*0.707;
        const double y_=std::cos(double(std::rand()))*0.707;
        ans.emplace_back(
            static_cast<float>(x_+y_),
            static_cast<float>(x_-y_));
    }
    return std::move(ans);
}


inline QList<QPointF> genCircle(double cx_,double cy_,double r_) {
    r_=std::abs(r_);
    if ((r_>0)==false) { return QList<QPointF>{}; }
    enum {SIZE=180};
    const static double pi_=4*std::atan(1.0);
    const static double step_pi_=pi_/SIZE*2.0;
    const static std::vector<QPointF> ans_=[]()->std::vector<QPointF> {
        std::vector<QPointF> ans; ans.reserve(SIZE+2);
        double step_=0;
        for (std::intptr_t n=0; n<SIZE;++n) {
            ans.emplace_back(std::sin(step_),std::cos(step_));
            step_+=step_pi_;
        }
        ans.push_back(ans[0]);
        return std::move(ans);
    }();
    QList<QPointF> ans;
    ans.reserve( ans_.size() );
    if ((r_==1)&&(cx_==0)&&(cy_==0)) {
        for (const auto & i:ans_) { ans.push_back(i); }
    }
    else if ((r_==1)&&(cx_==0)) {
        for (const auto & i:ans_) { 
            ans.push_back({ i.x(),i.y()+cy_ });
        }
    }
    else if ((r_==1)&&(cy_==0)) {
        for (const auto & i:ans_) {
            ans.push_back({ i.x()+cx_,i.y() });
        }
    }
    else if(r_==1){
        for (const auto & i:ans_) { 
            ans.push_back({ i.x()+cx_,i.y()+cy_ });
        }
    }
    else if((cy_==0)&&(cx_==0)){
        for (const auto & i:ans_) { 
            ans.push_back({ r_*i.x() ,r_*i.y()  });
        }
    }
    else if (cy_==0) {
        for (const auto & i:ans_) { 
            ans.push_back({ r_*i.x()+cx_ ,r_*i.y()  });
        }
    }
    else if (cx_==0) {
        for (const auto & i:ans_) { 
            ans.push_back({ r_*i.x() ,r_*i.y() +cy_ });
        }
    }
    else {
        for (const auto & i:ans_) { 
            ans.push_back({ r_*i.x()+cx_,r_*i.y()+cy_ });
        }
    }
    return std::move(ans) ;
}
    
}

 

extern void run(OpenCVWindow * window) try{

    std::vector<cv::Point2f> points_input=
        genRandPoint();

    auto * item_ = window->insertScatter(points_input.begin(),points_input.end());
    item_->setWindowTitle(u8"外接圆"_qs);

    cv::Point2f center;
    float radius;
    cv::minEnclosingCircle( points_input,center, radius);
    
    std::cout<<radius<<" "<<center<<std::endl;

    /*绘制外接圆形*/
    QtCharts::QLineSeries * series_=new QtCharts::QLineSeries;
    series_->append(genCircle(center.x,center.y,radius));
    series_->setPen(QPen(QColor(0,0,0),1));
    auto * chart_=item_->getChart();
    chart_->addSeries(series_);
    chart_->setAxisX(chart_->axisX(item_->getScatterSeries()),series_);
    chart_->setAxisY(chart_->axisY(item_->getScatterSeries()),series_);
    series_->setPointsVisible(true);
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}