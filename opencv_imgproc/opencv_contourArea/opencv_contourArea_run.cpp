/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include "private/opencv_contourArea_run_exception.cpp"
#include <QtCore/qdebug.h>
//#include <QtCharts>
namespace opencv_contourArea{
extern void run(OpenCVWindow * window) try {

    /*测试图片显示*/
    {

        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        QList<qreal> varContoursArea;

        for (const auto & image_name:images_names) {
            std::vector<std::vector<cv::Point>> varContoursPoints;
            {
                QImage varInputImage(image_name);
                cv::Mat varInputImageMat=
                    OpenCVUtility::tryRead(varInputImage);
                cv::findContours(
                    varInputImageMat,
                    varContoursPoints,
                    cv::RETR_EXTERNAL,
                    cv::CHAIN_APPROX_SIMPLE);
            }
            assert( varContoursPoints.empty()==false );
            auto varAns = cv::contourArea(varContoursPoints[0]) ;
            std::cout<<varAns<<",";
            varContoursArea.push_back(varAns);
        }

        if (false==varContoursArea.isEmpty()) {
            for (auto & vari:varContoursArea) {
                vari-=6000;
                vari/=6000;
                vari*=100;
            }
            window->insertHist(std::move(varContoursArea))
                ->setWindowTitle(u8"(检测值-6000)/6000的百分比"_qs);
        }
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}

}
