/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_Sobel_run_exception.cpp"
//#include <QtCharts>

namespace opencv_Sobel {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    if (images_names.isEmpty()) { return; }

    for (const auto & image_name:images_names) {
        cv::Mat image=OpenCVUtility::tryRead(
            QImage(image_name).convertToFormat(QImage::Format_Grayscale8)
            );
        window->insertImage(QImage(image_name))
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

        {
            cv::Mat dx,dy,ans;
            cv::Sobel(image,dx,CV_32F,1,0);
            cv::Sobel(image,dy,CV_32F,0,1);

            window->insertImage(cv::Mat(cv::abs(cv::abs(dx)-cv::abs(dy))))
                ->setWindowTitle(u8"第%1幅图片结果(dx-dy)"_qs.arg(count_));

            window->insertImage(cv::Mat(cv::abs(cv::abs(dx)+cv::abs(dy))))
                ->setWindowTitle(u8"第%1幅图片结果(dx+dy)"_qs.arg(count_));
        }

    }/*~for*/

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

