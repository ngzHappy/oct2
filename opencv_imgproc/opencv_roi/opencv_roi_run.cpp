/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include "private/opencv_roi_run_exception.cpp"

namespace opencv_roi{
extern void run(OpenCVWindow * window ) try{
    window->insertImage(QImage("images:000007"));
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

}
