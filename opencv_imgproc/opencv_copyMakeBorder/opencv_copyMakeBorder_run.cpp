/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_copyMakeBorder_run_exception.cpp"
//#include <QtCharts>

namespace opencv_copyMakeBorder {
extern void run(OpenCVWindow * window) try {
    enum {BorderSize=100};
    cv::Mat input;
    {
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        if (images_names.isEmpty()) { return; }

        auto imageName=images_names.first();
        input=OpenCVUtility::tryRead(QImage(imageName));
    }

    window->insertImage(input)->setWindowTitle(u8"原始图片"_qs);
    {
        cv::Mat ans;
        cv::copyMakeBorder(
            input,
            ans,
            BorderSize,BorderSize,BorderSize,BorderSize,
            cv::BORDER_CONSTANT
            );
        window->insertImage(ans)->setWindowTitle(u8"cv::BORDER_CONSTANT"_qs);
    }
    {
        cv::Mat ans;
        cv::copyMakeBorder(
            input,
            ans,
            BorderSize,BorderSize,BorderSize,BorderSize,
            cv::BORDER_REPLICATE 
            );
        window->insertImage(ans)->setWindowTitle(u8"cv::BORDER_REPLICATE "_qs);
    }
    {
        cv::Mat ans;
        cv::copyMakeBorder(
            input,
            ans,
            BorderSize,BorderSize,BorderSize,BorderSize,
            cv::BORDER_REFLECT 
            );
        window->insertImage(ans)->setWindowTitle(u8"cv::BORDER_REFLECT  "_qs);
    }
    {
        cv::Mat ans;
        cv::copyMakeBorder(
            input,
            ans,
            BorderSize,BorderSize,BorderSize,BorderSize,
            cv::BORDER_WRAP
            );
        window->insertImage(ans)->setWindowTitle(u8"cv::BORDER_WRAP  "_qs);
    }
    {
        cv::Mat ans;
        cv::copyMakeBorder(
            input,
            ans,
            BorderSize,BorderSize,BorderSize,BorderSize,
            cv::BORDER_REFLECT_101
            );
        window->insertImage(ans)->setWindowTitle(u8"cv::BORDER_REFLECT_101  "_qs);
    }
    /*{
        cv::Mat ans;
        cv::copyMakeBorder(
            input,
            ans,
            BorderSize,BorderSize,BorderSize,BorderSize,
            cv::BORDER_TRANSPARENT 
            );
        window->insertImage(ans)->setWindowTitle(u8"cv::BORDER_TRANSPARENT "_qs);
    }*/
}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

