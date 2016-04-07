/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

namespace {

inline double pi_() {static double pi__=std::atan(1.0)*4;
    return pi__;
}

inline double pi2_() {static double pi_2_=pi_()*2;
    return pi_2_;
}

constexpr inline float to_float(long double v)
{return static_cast<float>(v);}

inline std::vector<cv::Point2f>
genRandPoint() {
    enum { SIZE=100 };
    std::vector<cv::Point2f> ans;
    ans.reserve(SIZE);
    const double half_pi_=pi_()/2;
    const double step_=pi2_()/6;
    const std::vector<cv::Point2f> test_triangle{
        {std::sin(to_float(half_pi_)),std::cos(to_float(half_pi_))},
        {std::sin(to_float(half_pi_+step_)),std::cos(to_float(half_pi_+step_))},
        {std::sin(to_float(half_pi_+step_*2)),std::cos(to_float(half_pi_+step_*2))},
        {std::sin(to_float(half_pi_+step_*3)),std::cos(to_float(half_pi_+step_*3))},
        {std::sin(to_float(half_pi_+step_*4)),std::cos(to_float(half_pi_+step_*4))},
        {std::sin(to_float(half_pi_+step_*5)),std::cos(to_float(half_pi_+step_*5))},
    };
    for (std::intptr_t i=0; i<SIZE; ++i) {
    rand_begin_:
        const double x_=std::sin(double(std::rand()))*0.707;
        const double y_=std::cos(double(std::rand()))*0.707;
        if (cv::pointPolygonTest(test_triangle,cv::Point2f(x_,y_),false)<0) {
            goto rand_begin_;
        }
        ans.emplace_back(
            static_cast<float>(x_+y_),
            static_cast<float>(x_-y_));
    }
    return std::move(ans);
}

}

extern void run(OpenCVWindow * window) {

    std::vector<cv::Point2f> points_input=
        genRandPoint();

    auto * item_ = window->insertScatter(points_input.begin(),points_input.end());
    item_->setWindowTitle(u8"外接三角形"_qs);

}

