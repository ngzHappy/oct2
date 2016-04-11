/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_fitEllipse_run_exception.cpp"
#include <QtCharts>

extern void run(OpenCVWindow * window) try{

    std::vector<cv::Point2f> varPointsInput;

    varPointsInput=
        CoreUtility::getConfigurationFile()
        .getInputData2D<float,std::vector< cv::Point2f >/**/>();

    auto varEllipse = cv::fitEllipse(varPointsInput);

    auto varItem = window->insertScatter(
        varPointsInput.begin(),
        varPointsInput.end()
        );

    varItem->setWindowTitle(u8"椭圆拟合"_qs);
    varItem->resize(768-30,512-30);
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

