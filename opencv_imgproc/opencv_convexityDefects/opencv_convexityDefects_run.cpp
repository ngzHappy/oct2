/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_convexityDefects_run_exception.cpp"
#include <QtCharts>

namespace opencv_convexityDefects {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        QImage varImageInput=QImage(image_name);
        varImageInput=varImageInput.convertToFormat(QImage::Format_Grayscale8);
        auto varItem=window->insertChartImage(varImageInput);
        varItem->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        varItem->setGridLineVisible(false,false);

        std::vector<cv::Point> varContour=[]
            (QImage && argImage)->std::vector<cv::Point> {
            auto varMat=OpenCVUtility::tryRead(std::move(argImage));
            std::vector< std::vector<cv::Point> > varAns;
            cv::findContours(
                varMat,
                varAns,
                cv::RETR_EXTERNAL,
                cv::CHAIN_APPROX_NONE
                );
            if (varAns.empty()) { return{}; }
            std::sort(varAns.begin(),varAns.end(),
                [](auto & l,auto & r) {return l.size()>r.size(); });
            cv::approxPolyDP(varAns[0],varAns[0],3.2,false);
            varAns.resize(1);
            return std::move(varAns[0]);
        }(std::move(varImageInput));

        std::vector<cv::Point> varConvexHull;
        std::vector<std::int32_t> varConvexHullIndex;

        {
            std::vector<cv::Point> convexHull;
            cv::convexHull(varContour,convexHull);
            varConvexHull=std::move(convexHull);
        }
        {
            std::vector<std::int32_t> convexHull;
            cv::convexHull(varContour,convexHull,false);
            varConvexHullIndex=std::move(convexHull);
        }

        std::vector<cv::Vec4i> varAns;

        cv::convexityDefects(
            varContour,
            varConvexHullIndex,
            varAns
            );

        {
            /*绘制凸包*/
            varItem->insertLine(
                varConvexHull.begin(),
                varConvexHull.end(),
                true);
        }

        {/*绘制结果曲线*/
            QList<QPointF> varAboutToDraw;
            for (const auto & i:varAns) {
                /*绘制起点 最远点 终点*/
                varAboutToDraw.push_back(QPointF(varContour[i[0]].x,varContour[i[0]].y));
                varAboutToDraw.push_back(QPointF(varContour[i[2]].x,varContour[i[2]].y));
                varAboutToDraw.push_back(QPointF(varContour[i[1]].x,varContour[i[1]].y));
            }
            varItem->insertLine(
                varAboutToDraw,true)->setPen({ QColor(255,30,50,150),2 });
        }

    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

//answers.opencv.org/question/81942/convexity-defect-not-working-as-expected/
//https://github.com/Itseez/opencv/issues/5908
