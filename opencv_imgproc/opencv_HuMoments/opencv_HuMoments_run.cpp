/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_HuMoments_run_exception.cpp"
//#include <QtCharts>

namespace opencv_HuMoments {
extern void run(OpenCVWindow * window) try {
    QList<std::vector<double>> HuMoments;
    {
        auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        if (images_names.isEmpty()) { return; }

        std::list<QImage> images;
        for (const auto & image_name:images_names) {
            images.push_back(QImage(image_name)
                .convertToFormat(QImage::Format_Grayscale8));
        }

        std::list<std::vector<cv::Point>> contours;

        for (auto & i:images) {
            cv::Mat mat_=OpenCVUtility::tryRead(i);
            std::vector<std::vector<cv::Point>> ans;
            cv::findContours(mat_,ans,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);
            std::sort(ans.begin(),ans.end(),
                [](auto & l,auto &r) {return l.size()>r.size(); });
            if (ans.empty()) { continue; }
            contours.push_back(std::move(ans[0]));
        }

        auto first_contour=contours.begin();
        auto end_contour=contours.end();
        for (auto pos=first_contour; pos!=end_contour; ++pos) {
            std::vector<double> ans;
            cv::HuMoments(cv::moments(*pos),ans);
            HuMoments.push_back(std::move(ans));
        }

    }

    std::vector<QList<QPointF>> linesData;
    linesData.resize(7);
    std::int32_t index=0;
    for(const auto & i:HuMoments){
        linesData[0].push_back(QPointF(index,i[0]));
        linesData[1].push_back(QPointF(index,i[1]));
        linesData[2].push_back(QPointF(index,i[2]));
        linesData[3].push_back(QPointF(index,i[3]));
        linesData[4].push_back(QPointF(index,i[4]));
        linesData[5].push_back(QPointF(index,i[5]));
        linesData[6].push_back(QPointF(index,i[6]));
        ++index;
    }

    index=0;
    for (const auto & i:linesData) {
        window->insertLineSeries(i)
            ->setWindowTitle(u8"第%1条曲线"_qs.arg(index++));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

