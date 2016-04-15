/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_matchShapes_run_exception.cpp"
#include <list>
//#include <QtCharts>

namespace opencv_matchShapes {
extern void run(OpenCVWindow * window) try {

    auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    if (images_names.isEmpty()) { return; }
     
    std::list<QImage> images;
    for (const auto & image_name:images_names) {
        images.push_back(QImage(image_name)
            .convertToFormat(QImage::Format_Grayscale8));
    }
    
    window->insertImage(*images.begin())
        ->setWindowTitle(u8"第一幅图片"_qs);

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

    QList<qreal> matchAns;
    auto first_contour=contours.begin();
    auto end_contour=contours.end();
    for (auto pos=first_contour;pos!=end_contour;++pos) {
        matchAns.push_back( cv::matchShapes(
            *first_contour,
            *pos,
            CV_CONTOURS_MATCH_I2 ,
            0/*no effect*/));
    }

    window->insertHist(std::move(matchAns))
        ->setWindowTitle(u8"对比结果"_qs);

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}

}/*~namespace*/

