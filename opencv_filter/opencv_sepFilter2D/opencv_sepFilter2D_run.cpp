/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_sepFilter2D_run_exception.cpp"
//#include <QtCharts>

namespace opencv_sepFilter2D {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {

        QImage image_input=QImage(image_name);
        image_input=image_input.convertToFormat(QImage::Format_RGB888);

        cv::Mat mat=OpenCVUtility::tryRead(image_input);
        mat.convertTo(mat,CV_32FC3);

        cv::Mat kernel = cv::getGaussianKernel(7, 1.5, CV_32F);
        cv::sepFilter2D(
            mat,
            mat,
            CV_32F,
            kernel,
            kernel
            );

        window->insertImage(image_input)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        window->insertImage(mat)
            ->setWindowTitle(u8"第%1幅图片结果"_qs.arg(count_));
    }


}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

