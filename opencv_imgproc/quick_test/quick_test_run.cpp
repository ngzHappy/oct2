/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/quick_test_run_exception.cpp"
#include <QtCharts>

namespace quick_test {
extern void run(OpenCVWindow * window) try {

    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    if (images_names.isEmpty()) { return; }

    auto image_name=images_names.first();
    QImage image(image_name);
    
    cv::Mat mat=OpenCVUtility::tryRead(image);
    cv::cvtColor(mat,mat,cv::COLOR_RGB2GRAY);

    window->insertImage(image)->setWindowTitle(u8"原始图像"_qs);

    cv::Mat gradY,gradX;
    cv::Sobel(mat,gradX,CV_32F,1,0,-1);
    cv::Sobel(mat,gradY,CV_32F,0,1,-1);

    window->insertImage(OpenCVUtility::tryRead(gradX))
        ->setWindowTitle(u8"scharr x"_qs);
    window->insertImage(OpenCVUtility::tryRead(gradY))
        ->setWindowTitle(u8"scharr y"_qs);

    cv::Mat gradient=gradX-gradY;
    cv::convertScaleAbs(gradient,gradient);

    window->insertImage(OpenCVUtility::tryRead(gradient))
        ->setWindowTitle(u8"scharr abs(x-y)"_qs);

    cv::Mat blurred;
    cv::blur(gradient,blurred,{ 9 ,9});

    window->insertImage(OpenCVUtility::tryRead(blurred))
        ->setWindowTitle(u8"blur gradient"_qs);

    cv::Mat thresh;
    cv::threshold(blurred,thresh,225,255,cv::THRESH_BINARY);
    window->insertImage(OpenCVUtility::tryRead(thresh))
        ->setWindowTitle(u8"blur gradient"_qs);

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

