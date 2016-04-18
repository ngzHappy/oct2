/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_pyrMeanShiftFiltering_run_exception.cpp"
//#include <QtCharts>

namespace opencv_pyrMeanShiftFiltering {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        QImage inputImage=QImage(image_name);
        if (inputImage.isNull()) { continue; }
        inputImage=inputImage.convertToFormat(QImage::Format_RGB888);
        window->insertImage(inputImage)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        cv::Mat image=OpenCVUtility::tryRead(inputImage);
        cv::Mat ans;
        cv::pyrMeanShiftFiltering(image,ans,19,22,2);
        window->insertImage(ans)
            ->setWindowTitle(u8"第%1幅图片结果"_qs.arg(count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

