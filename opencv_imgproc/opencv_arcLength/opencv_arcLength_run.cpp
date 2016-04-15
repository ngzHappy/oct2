/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_arcLength_run_exception.cpp"
//#include <QtCharts>
namespace opencv_arcLength{
extern void run(OpenCVWindow * window) try{

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
            cv::approxPolyDP(varContoursPoints[0],varContoursPoints[0],5,true);
            auto varAns = cv::arcLength(varContoursPoints[0],true) ;
            std::cout<<varAns<<",";
            varContoursArea.push_back(varAns);
        }

        if (false==varContoursArea.isEmpty()) {
            for (auto & vari:varContoursArea) {
                vari-=320;
                vari/=320;
                vari*=320;
            }
            window->insertHist(std::move(varContoursArea))
                ->setWindowTitle(u8"(检测值-320)/320的百分比"_qs);
        }
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}
}
