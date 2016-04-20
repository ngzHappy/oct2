/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_matchTemplate_run_exception.cpp"
#include "OpenCVWindowDetail.hpp"
#include "ControlItem.hpp"
//#include <QtCharts>

OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage inputImage) {
    OpenCVImageItem * ans =OpenCVWindow::insertImage(inputImage);
    auto * var_vi= new OpenCVVerticalItems(ans);
    var_vi->addWidget(new ControlItem);
    ans->resize(
        inputImage.width()+360,
        inputImage.height()+360
    );
    return ans;
}

namespace opencv_matchTemplate {
extern void run(OpenCVWindow * window) try {

    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");
    std::intptr_t count_=0;
    for (const auto & image_name:images_names) {
        window->insertImage(QImage(image_name))
            ->setWindowTitle(u8"%1"_qs.arg(++count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

