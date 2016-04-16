/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_dilate_run_exception.cpp"
//#include <QtCharts>

namespace opencv_dilate {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {

        QImage image_input=QImage(image_name);

        image_input=image_input.convertToFormat(
            QImage::Format_Grayscale8);

        window->insertImage(image_input)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

        cv::Mat vimage=OpenCVUtility::tryRead(image_input);
        auto selement=cv::getStructuringElement(cv::MORPH_RECT,{ 5,5 });
        cv::Mat vans;
        cv::dilate(vimage,vans,selement);
        window->insertImage(vans)
            ->setWindowTitle(u8"第%1幅图片结果"_qs.arg(count_));
        window->insertImage(cv::Mat(cv::abs(vimage-vans)))
            ->setWindowTitle(u8"第%1幅图片结果-原图"_qs.arg(count_));
    }


}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

