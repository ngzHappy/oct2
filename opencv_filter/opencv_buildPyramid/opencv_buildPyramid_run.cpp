/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_buildPyramid_run_exception.cpp"
//#include <QtCharts>

namespace opencv_buildPyramid {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    if (images_names.isEmpty()) { return; }

    for (const auto & image_name:images_names) {
        QImage image_input(image_name);
        window->insertImage(image_input)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        std::vector<cv::Mat> ans;
        cv::buildPyramid(
            OpenCVUtility::tryRead(image_input),
            ans,4);
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

