/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
//#include <QtCharts>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
namespace {
int ErrorCallback(
    int status/*cv::Error::Code*/,
    const char* func_name,
    const char* err_msg,
    const char* file_name,
    int line,
    void* /*userdata*/) {
    QString __error_;

#if !defined(NDEBUG)
    cv::Error::Code estatus= static_cast<cv::Error::Code>(status);
    (void)estatus;
#endif

    {
        QTextStream stream_(&__error_);
        stream_
            <<"function name:"<<func_name
            <<"error message:"<<err_msg
            <<"file name:"<<file_name
            <<"line:"<<line;
    }

    if (qApp) {
        QErrorMessage errorBox;
        errorBox.showMessage(__error_,"error");
        errorBox.exec();
    }
    else {
        qDebug().noquote()<<__error_;
    }

    return 0;
    (void)status;
}
}
/*当qapplication运行时注册此函数*/
static void _set_opencv_error_on_qt_start_up() {
    cv::redirectError(&ErrorCallback);
}
Q_COREAPP_STARTUP_FUNCTION(_set_opencv_error_on_qt_start_up)

extern void run(OpenCVWindow *) try{

    {
        const auto images_names=
            CoreUtility::getConfigurationFile()
            .getInputImagesNames("images:000001");

        for (const auto & in_:images_names) {
            qDebug()<<in_;
        }
    }

    {
        qDebug()<<"data 1d";
        auto data_1d=CoreUtility::getConfigurationFile()
            .getInputData1D();
        for (const auto & i:data_1d) {
            qDebug()<<i;
        }
    }

    {
        qDebug()<<"data 1d";
        std::vector<float> data_1d;
        CoreUtility::getConfigurationFile()
            .getInputData1D<float>( std::back_inserter(data_1d) );
        for (const auto & i:data_1d) {
            qDebug()<<i;
        }
    }

    {
        qDebug()<<"data 2d";
        auto data_2d=CoreUtility::getConfigurationFile()
            .getInputData2D<float,std::vector<cv::Point2f>>();
        for (const auto & i:data_2d) {
            qDebug()<<i.x<<i.y;
        }
    }

    {
        qDebug()<<"data 2d";
        std::vector<cv::Point2f> data_2d;
        CoreUtility::getConfigurationFile()
            .getInputData2D<float>( std::back_inserter(data_2d) );
        for (const auto & i:data_2d) {
            qDebug()<<i.x<<i.y;
        }
    }

    {
        qDebug()<<"data 3d";
        auto data_3d=CoreUtility::getConfigurationFile()
            .getInputData3D();
        for (const auto & i:data_3d) {
            qDebug()<<i[0]<<i[1]<<i[2];
        }
    }

    {
        qDebug()<<"data 3d";
        std::vector<std::array<float,3>> data_3d;
        CoreUtility::getConfigurationFile()
            .getInputData3D<float>( std::back_inserter(data_3d) );
        for (const auto & i:data_3d) {
            qDebug()<<i[0]<<i[1]<<i[2];
        }
    }

    {
        qDebug()<<"data 1d Integer";
        auto data_1d=CoreUtility::getConfigurationFile()
            .getInputData1DInteger();
        for (const auto & i:data_1d) {
            qDebug()<<i;
        }
    }

    {
        qDebug()<<"data 1d Integer";
        std::vector<int> data_1d;
        CoreUtility::getConfigurationFile()
            .getInputData1DInteger<int>(std::back_inserter(data_1d));
        for (const auto & i:data_1d) {
            qDebug()<<i;
        }
    }

    {
        qDebug()<<"data 2d Integer";
        auto data_2d=CoreUtility::getConfigurationFile()
            .getInputData2DInteger();
        for (const auto & i:data_2d) {
            qDebug()<<i.first<<i.second;
        }
    }

    {
        qDebug()<<"data 2d Integer";
        std::vector<std::pair<int,int>> data_2d;
        CoreUtility::getConfigurationFile()
            .getInputData2DInteger<int>(std::back_inserter(data_2d));
        for (const auto & i:data_2d) {
            qDebug()<<i.first<<i.second;
        }
    }

    {
        qDebug()<<"data 3d Integer";
        auto data_3d=CoreUtility::getConfigurationFile()
            .getInputData3DInteger();
        for (const auto & i:data_3d) {
            qDebug()<<i[0]<<i[1]<<i[2];
        }
    }

    {
        qDebug()<<"data 3d Integer";
        std::vector<std::array<int,3>> data_3d;
        CoreUtility::getConfigurationFile()
            .getInputData3DInteger<int>(std::back_inserter(data_3d));
        for (const auto & i:data_3d) {
            qDebug()<<i[0]<<i[1]<<i[2];
        }
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}
