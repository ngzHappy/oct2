/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_Scharr_run_exception.cpp"
//#include <QtCharts>

namespace opencv_Scharr {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        QImage inputImage=QImage(image_name);
        inputImage=inputImage.convertToFormat(QImage::Format_Grayscale8);
        window->insertImage(inputImage)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        cv::Mat image=OpenCVUtility::tryRead(inputImage);
        cv::Mat dx,dy;
        cv::Scharr(image,dx,CV_32F,1,0);
        cv::Scharr(image,dy,CV_32F,0,1);
        dx=abs(dx); dy=abs(dy);
        window->insertImage(dx)
            ->setWindowTitle(u8"第%1幅图片dx"_qs.arg(count_));
        window->insertImage(dy)
            ->setWindowTitle(u8"第%1幅图片dy"_qs.arg(count_));
    }


}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

