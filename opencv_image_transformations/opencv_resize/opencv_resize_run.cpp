/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_resize_run_exception.cpp"
//#include <QtCharts>

namespace opencv_resize {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        QImage imageInput=QImage(image_name);
        window->insertImage(imageInput)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

        cv::Mat image=OpenCVUtility::tryRead(imageInput);
        cv::Mat ans;
        cv::resize(image,ans,{},
            0.5+((rand()%200)/200.0),
            0.5+((rand()%200)/200.0));
        window->insertImage(ans)
            ->setWindowTitle(u8"第%1幅图片结果"_qs.arg(count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

