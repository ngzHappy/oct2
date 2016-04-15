/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_applyColorMap_run_exception.cpp"
//#include <QtCharts>
/*
enum  	cv::ColormapTypes {
  cv::COLORMAP_AUTUMN = 0,
  cv::COLORMAP_BONE = 1,
  cv::COLORMAP_JET = 2,
  cv::COLORMAP_WINTER = 3,
  cv::COLORMAP_RAINBOW = 4,
  cv::COLORMAP_OCEAN = 5,
  cv::COLORMAP_SUMMER = 6,
  cv::COLORMAP_SPRING = 7,
  cv::COLORMAP_COOL = 8,
  cv::COLORMAP_HSV = 9,
  cv::COLORMAP_PINK = 10,
  cv::COLORMAP_HOT = 11,
  cv::COLORMAP_PARULA = 12
}*/

namespace  {
inline int genType(){return rand()%13;}
}

namespace opencv_applyColorMap{
extern void run(OpenCVWindow * window) try{

    /*测试图片显示*/
    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

            for (const auto & image_name:images_names) {
                QImage varInputImage = QImage(image_name);
                varInputImage = varInputImage.convertToFormat(QImage::Format_Grayscale8);
                cv::Mat varOCVImage = OpenCVUtility::tryRead(varInputImage);
                cv::Mat varAns;
                cv::applyColorMap(varOCVImage,varAns,genType());
                window->insertImage( OpenCVUtility::tryRead(std::move(varAns)) )
                    ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        }
    }


}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}

}
