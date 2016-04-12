/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include <OpenCVBoost.hpp>
#include "private/boost_simple_test_run_exception.cpp"
//#include <QtCharts>

extern void run(OpenCVWindow * ) try{

    {
        boost::shared_ptr<int> value=boost::make_shared<int>(12);
        assert(value);
        assert(*value==12);
    }

    {
        boost::pool<> testPool{ 16 };
        auto data=testPool.malloc();
        assert(data);
        (void)data;
    }

    {
        boost::circular_buffer<int> buffer{200};
    }

    {
        boost::optional<int> value;
        assert(bool(value)==false);
        value=12;
        assert(value);
    }

    {
        boost::signals2::signal<void(void)> signal;
        auto sc= signal.connect([]() {std::cout<<"1"<<std::endl; });
        signal();
        sc.disconnect();
        signal();
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

