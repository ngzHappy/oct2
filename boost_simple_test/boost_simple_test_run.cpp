/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include <OpenCVBoost.hpp>
#include "private/boost_simple_test_run_exception.cpp"
//#include <QtCharts>

extern void run(OpenCVWindow * ) try{

    boost::shared_ptr<int> value=boost::make_shared<int>(12);
    assert( value );
    assert( *value==12 );

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

