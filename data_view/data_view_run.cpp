/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
//#include <QtCharts>
#include "private/data_view_run_exception.cpp"

namespace data_view{
extern void run(OpenCVWindow * window ) try{

    /*图片显示*/
    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("");

        for (const auto & image_name:images_names) {
            if (image_name.isEmpty()) { continue; }
            auto * item=window->insertChartImage(QImage(image_name));
            item->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
            item->setGridLineVisible(false,false);
        }
    }

    /*2d数据显示*/
    {
        auto points_2d=
        CoreUtility::getConfigurationFile().
            getInputData2D<qreal,QList<QPointF>>();
        if (points_2d.isEmpty()==false) {
            auto * item=window->insertScatter(points_2d);
            item->setWindowTitle(u8"散点图"_qs);
        }
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}
