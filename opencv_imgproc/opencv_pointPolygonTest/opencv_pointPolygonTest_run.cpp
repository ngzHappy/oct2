/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_pointPolygonTest_run_exception.cpp"
//#include <QtCharts>

extern void run(OpenCVWindow * window) try{

    enum{ LENGTH_=32 };
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");
    std::int32_t varPictureIndex=0;
    for (const auto & varImageName:images_names) {

        if (varImageName.isEmpty()) { return; }

        QImage varImage(varImageName);
        if (varImage.width()<LENGTH_) { continue; }
        if (varImage.height()<LENGTH_) { continue; }
        ++varPictureIndex;
        window->insertImage(varImage)
            ->setWindowTitle(u8"原图%1"_qs.arg(varPictureIndex));
        varImage=varImage.convertToFormat(QImage::Format_RGBA8888);

        cv::Mat varImageMat=OpenCVUtility::tryRead(varImage);
        std::vector<cv::Point> varContour;
        {
            std::vector<std::vector<cv::Point>> varContours;
            cv::Mat varImageTemplate=OpenCVUtility::tryRead(
                        QImage("images:030001").convertToFormat(QImage::Format_Grayscale8)
                        );
            cv::resize(varImageTemplate,varImageTemplate,varImageMat.size());
            cv::findContours(
                        varImageTemplate,
                        varContours,
                        cv::RETR_EXTERNAL,
                        cv::CHAIN_APPROX_SIMPLE
                        );
            if (varContours.empty()) { return; }
            varContour=std::move(varContours[0]);
        }

        for (std::int_fast32_t varX=0; varX<varImageMat.cols; ++varX) {
            for (std::int_fast32_t varY=0; varY<varImageMat.rows; ++varY) {
                auto varLength=cv::pointPolygonTest(
                                     varContour,
                                     cv::Point2f(varX,varY),
                                     true);
                const cv::Point varPoint(varX,varY);
                if (varLength>0) {
                    if (varLength>LENGTH_) {
                        varImageMat
                            .at<std::array<unsigned char,4>>(varPoint)[3]=(unsigned char)(0x00ff);
                    }
                    else {
                        varLength/=LENGTH_;
                        varLength*=255.9998;
                        varImageMat
                            .at<std::array<unsigned char,4>>(varPoint)[3]=(unsigned char)(varLength);
                    }
                }
                else {
                    varImageMat
                        .at<std::array<unsigned char,4>>(varPoint)[3]=0;
                }
            }
        }
        window->insertImage(varImage)
            ->setWindowTitle(u8"心形%1"_qs.arg(varPictureIndex));
    }
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

