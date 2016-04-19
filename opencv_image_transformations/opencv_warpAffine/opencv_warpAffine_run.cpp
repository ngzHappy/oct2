/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_warpAffine_run_exception.cpp"
//#include <QtCharts>

namespace opencv_warpAffine {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        QImage imageInput=QImage(image_name);
        window->insertImage(imageInput)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

        auto imageHeigth=imageInput.height();
        auto imageWidth=imageInput.width();

        std::vector< cv::Point2f > varFrom{
            cv::Point2f(0,0),
            cv::Point2f(0,imageHeigth),
            cv::Point2f(imageWidth,0),
        };

        std::vector< cv::Point2f > varTo{
            cv::Point2f(0,imageHeigth/4.0),
            cv::Point2f(imageWidth/4.0,imageHeigth),
            cv::Point2f(imageWidth/4.0*3,0),
        };

        cv::Mat matrixAffineTransform = cv::getAffineTransform(varFrom,varTo);

        cv::Mat ans;
        cv::Mat image=OpenCVUtility::tryRead(imageInput);
        cv::warpAffine(
            image,
            ans,
            matrixAffineTransform,
            image.size()
        );

        window->insertImage(ans)
            ->setWindowTitle(u8"第%1幅图片结果"_qs.arg(count_));

    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

