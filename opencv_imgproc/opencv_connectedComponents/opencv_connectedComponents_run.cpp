/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_connectedComponents_run_exception.cpp"
//#include <QtCharts>
namespace opencv_connectedComponents{
extern void run(OpenCVWindow * window) try{

    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

            for (const auto & image_name:images_names) {
                QImage varInputImage=QImage(image_name);
                varInputImage=varInputImage.convertToFormat(QImage::Format_Grayscale8);
                cv::Mat varImage=OpenCVUtility::tryRead(varInputImage);
                cv::Mat varAns;
                qDebug()<< cv::connectedComponents(varImage,varAns);
                cv::normalize(varAns,varAns,0,255,CV_MINMAX);
                window->insertImage(OpenCVUtility::tryRead(std::move(varAns)))
                    ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        }
    }


}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}
}
