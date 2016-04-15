/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_boxFilter_run_exception.cpp"
//#include <QtCharts>

namespace opencv_boxFilter {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        cv::Mat image=OpenCVUtility::tryRead(
            QImage(image_name).convertToFormat(QImage::Format_RGB888)
            );
        window->insertImage(image)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

        image.convertTo(image,CV_32FC3);
        cv::boxFilter(image,image,-1,{ 3,3 },{-1,-1},false);

        window->insertImage(image)
            ->setWindowTitle(u8"第%1幅图片滤波结果"_qs.arg(count_));
    }


}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

