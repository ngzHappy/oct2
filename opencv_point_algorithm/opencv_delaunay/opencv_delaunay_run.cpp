/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include <QtCharts>

namespace {

inline double rand_0_1() { return (rand()%10000)/10000.0;}

std::vector<cv::Point2f> genPoints() {
    std::vector<cv::Point2f> ans;
    enum {SIZE=10};
    
    const double x_start_=-1;
    const double y_start_=-1;

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

extern void run(OpenCVWindow * window) {

    /*随机生成测试数据*/
    std::vector<cv::Point2f> points = genPoints();
    /*绘制测试数据*/
    auto * item =
        window->insertScatter(points.begin(),points.end());

     

    item->setWindowTitle(u8"三角形剖分"_qs);
}

