/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_remap_run_exception.cpp"
//#include <QtCharts>

namespace opencv_remap {

namespace {
namespace __private {
template<
    typename _T_,
    typename _Function_,
    typename ... Args
>
static inline void value(
    _T_ * const startPointer_,
    const std::size_t width_,
    const std::size_t height_,
    std::size_t perLineSize_,
    const _Function_ & fun_/*function(_T_ * , ... )*/,
    Args && ... args_
) {
    if (perLineSize_<width_) { perLineSize_=width_; }
    _T_ * linePointer_=startPointer_;
    std::size_t y_=0;
    std::size_t x_=0;
    for (; y_<height_; ++y_) {
        _T_ * lineStart_=linePointer_;
        const _T_ * const lineEnd_=linePointer_+width_;
        for (x_=0; lineStart_!=lineEnd_; ++lineStart_,++x_) {
            fun_(lineStart_,x_,y_,std::forward<Args>(args_)...);
        }
        linePointer_+=perLineSize_;
    }
}
}
}

extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        
        QImage image0(image_name);
        window->insertImage(image0)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

        {
            const auto image_width_=image0.width();
            const auto image_height_=image0.height();

            /*flip x,y*/
            cv::Mat flipX(image_height_,image_width_,CV_32FC1);
            cv::Mat flipY(image_height_,image_width_,CV_32FC1);

            __private::value(
                flipX.ptr<float>(),
                image_width_,image_height_,
                (flipX.step.buf[0])/(flipX.step.buf[1]),
                [](
                float * data_,
                std::size_t x_,std::size_t,
                std::int32_t width__) {*data_=width__-x_; },
                image_width_-1
            );

            __private::value(
                flipY.ptr<float>(),
                image_width_,image_height_,
                (flipY.step.buf[0])/(flipY.step.buf[1]),
                [](
                float * data_,
                std::size_t ,std::size_t y_,
                std::int32_t height__) {*data_=height__-y_; },
                image_height_-1
            );

            auto cvImage_ = OpenCVUtility::tryRead(image0);
            cv::Mat ans;
            cv::remap(cvImage_,ans,flipX,flipY,cv::InterpolationFlags::INTER_LINEAR);

            window->insertImage( ans )
                ->setWindowTitle(QObject::trUtf8(u8"变换后图像%1").arg(count_));
        }

        {
            const auto image_width_=image0.width();
            const auto image_height_=image0.height();

            /*flip x,y*/
            cv::Mat flipX(image_height_,image_width_,CV_32FC1);
            cv::Mat flipY(image_height_,image_width_,CV_32FC1);

            enum {RandomSize=8};
            std::array<std::int32_t,RandomSize> randomX,randomY;
            for (int i=0; i<RandomSize; ++i) { 
                randomX[i]=i;randomY[i]=i;
            }

            std::shuffle(randomX.begin(),randomX.end(),
                std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
            std::shuffle(randomY.begin(),randomY.end(),
                std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

            __private::value(
                flipX.ptr<float>(),
                image_width_,image_height_,
                (flipX.step.buf[0])/(flipX.step.buf[1]),
                [&randomX](
                float * data_,
                std::size_t x_,std::size_t,
                std::size_t max_) {
                *data_=std::min<float>((x_/RandomSize*RandomSize)+randomX[(x_%RandomSize)],max_);
            },
                image_width_-1
                );

            __private::value(
                flipY.ptr<float>(),
                image_width_,image_height_,
                (flipY.step.buf[0])/(flipY.step.buf[1]),
                [&randomY](
                float * data_,
                std::size_t ,std::size_t y_,
                std::size_t max_) {
                *data_=std::min<float>((y_/RandomSize*RandomSize)+randomY[(y_%RandomSize)],max_);
            },
                image_height_-1
                );

            auto cvImage_ = OpenCVUtility::tryRead(image0);
            cv::Mat ans;
            cv::remap(cvImage_,ans,flipX,flipY,
                cv::InterpolationFlags::INTER_LINEAR);

            window->insertImage( ans )
                ->setWindowTitle(QObject::trUtf8(u8"随机晶格化%1").arg(count_));

        }

    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

