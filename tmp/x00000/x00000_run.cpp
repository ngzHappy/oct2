/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/x00000_run_exception.cpp"
//#include <QtCharts>

namespace x00000{
extern void run(OpenCVWindow * window) try{

    QString imageName;
    {
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");
        if (images_names.isEmpty()) { return; }
        imageName=images_names.first();
    }

    cv::Mat image=OpenCVUtility::tryRead(
        QImage(imageName).convertToFormat(QImage::Format::Format_Grayscale8)
        );



    window->insertImage(image);
   

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

