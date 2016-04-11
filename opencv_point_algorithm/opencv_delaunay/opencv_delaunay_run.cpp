/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCharts>
#include "private/opencv_delaunay_run_exception.cpp"

namespace {

inline double rand_0_1() { 
    enum :std::intptr_t{_D_=54321};
    return static_cast<double>(rand()%_D_)/_D_;
}

std::vector<cv::Point2f> genPoints() {
    std::vector<cv::Point2f> ans;
    enum {SIZE=10};
    
    const double x_start_=1;
    const double y_start_=1;

    const double step_x=2.0/SIZE;
    const double step_y=2.0/SIZE;

    ans.reserve(SIZE*SIZE);

    for (std::intptr_t ix=0; ix<SIZE;++ix) {
        for (std::intptr_t iy=0; iy<SIZE;++iy) {
            double x_=x_start_+ix*step_x;
            double y_=y_start_+iy*step_y;
            x_+=rand_0_1()/2*step_x;
            y_+=rand_0_1()/2*step_y;
            ans.emplace_back( static_cast<float>(x_),static_cast<float>(y_) );
        }
    }

    return std::move(ans);
}

}

extern void run(OpenCVWindow * window) try{

    /*随机生成测试数据*/
    std::vector<cv::Point2f> points = genPoints();
    /*绘制测试数据*/
    auto * item =
        window->insertScatter(points.begin(),points.end());

    /*创建三角形剖分器*/
    std::shared_ptr<cv::Subdiv2D> delanunay_ =
        std::make_shared<cv::Subdiv2D>(cv::Rect(1,1,2,2));
    auto & delanunay=*delanunay_;

    /*插入点*/
    delanunay.insert(points);

    /*获得结果*/
    std::vector< cv::Vec6f > ans;
    delanunay.getTriangleList(ans);

    std::cout<<ans.size()<<std::endl;

    /*绘制结果*/
    {
        auto * chart_=item->getChart();
        auto * axis_x=chart_->axisX(item->getScatterSeries())/*获得x轴*/;
        auto * axis_y=chart_->axisY(item->getScatterSeries())/*获得y轴*/;
        const QPen pen(QColor(0,0,0,100),2);
        for (const auto & i:ans) {
            QtCharts::QLineSeries * item_=new QtCharts::QLineSeries;
            item_->append(i[0],i[1])/*第一个点*/;
            item_->append(i[2],i[3])/*第二个点*/;
            item_->append(i[4],i[5])/*第三个点*/;
            item_->append(i[0],i[1])/*闭合三角形*/;
            chart_->addSeries(item_);
            chart_->setAxisX(axis_x,item_)/*设置此三角形x轴*/;
            chart_->setAxisY(axis_y,item_)/*设置此三角形y轴*/;
            item_->setPen(pen);
            item_->setPointsVisible(true);
        }
    }

    item->setWindowTitle(u8"三角形剖分"_qs);
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}
