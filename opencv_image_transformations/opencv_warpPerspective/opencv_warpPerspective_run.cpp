/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_warpPerspective_run_exception.cpp"
//#include <QtCharts>

namespace opencv_warpPerspective {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        QImage imageInput=QImage(image_name);
        window->insertImage(imageInput)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

        QImage image0=imageInput;

        const float width_image_=image0.width();
        const float height_image_=image0.height();

        const std::vector< cv::Point2f > from_{ 
            {0,0},
            {0,height_image_},
            {width_image_,height_image_}, 
            {width_image_,0} 
        };

        const std::vector< cv::Point2f > to_{ 
            {0,0},
            {0,height_image_},
            {width_image_,height_image_/4*3}, 
            {width_image_,height_image_/4} 
        };

        cv::Mat atmax_ = cv::getPerspectiveTransform(from_,to_);

        auto cvImage0=OpenCVUtility::tryRead(image0);

        auto ansSize=cv::Size(image0.width(),image0.height());
        cv::Mat ans;

        cv::warpPerspective(cvImage0,ans ,atmax_,ansSize);

        window->insertImage( ans )
            ->setWindowTitle(QObject::trUtf8(u8"变换后图像%1").arg(count_));

    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

