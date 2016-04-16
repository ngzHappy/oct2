/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_filter2D_run_exception.cpp"
//#include <QtCharts>

namespace opencv_filter2D {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        QImage input_image=QImage(image_name);

        cv::Mat core(3,3,CV_32FC1,cv::Scalar(1));
        {
            float * varData=core.ptr<float>();
            varData[4]=-8;
        }

        cv::Mat ans;
        cv::filter2D(
            OpenCVUtility::tryRead(input_image),
            ans,CV_32F,
            core);

        window->insertImage(input_image)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        window->insertImage(ans)
            ->setWindowTitle(u8"第%1幅图片结果"_qs.arg(count_));

    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

