/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include "private/opencv_pyrDown_run_exception.cpp"

namespace opencv_pyrDown{
extern void run(OpenCVWindow * window) try{

    intptr_t count_=0;
    /*从配置文件中获得输入图片*/
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");
    /*进行变换*/
    for (const auto & image_name:images_names) {
        ++count_;
        cv::Mat mat=OpenCVUtility::tryRead(QImage(image_name));
        window->insertImage(OpenCVUtility::tryRead(mat))
            ->setWindowTitle(u8"第%1幅原始图片"_qs.arg(count_));
        cv::Mat ans;
        cv::pyrDown( mat,ans,mat.size()/2 );
        window->insertImage(OpenCVUtility::tryRead(ans))
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}
}
