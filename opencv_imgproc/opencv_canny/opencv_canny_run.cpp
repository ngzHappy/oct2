/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include "private/opencv_canny_run_exception.cpp"
namespace  opencv_canny{

extern void run(OpenCVWindow * window) try{

    intptr_t count_=0;
    /*从配置文件中获得输入图片文件名*/
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");
    /*进行变换*/
    for (const auto & image_name:images_names) {
        ++count_;
        cv::Mat mat=OpenCVUtility::tryRead(QImage(image_name));
        window->insertImage(OpenCVUtility::tryRead(mat) )
            ->setWindowTitle(u8"第%1幅原始图片"_qs.arg(count_));
        cv::Mat ans;
        cv::blur(mat,ans,{3,3});/*平滑滤波*/
        cv::Canny(ans,ans,100,200);/*canny 边缘检测*/
        window->insertImage(OpenCVUtility::tryRead(ans) )
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

}
