/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
//#include <QtCharts>

extern void run(OpenCVWindow *) {

    /*测试图片*/
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
        qDebug()<<"data 2d";
        auto data_2d=CoreUtility::getConfigurationFile()
            .getInputData2D<float,std::vector<cv::Point2f>>();
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
        qDebug()<<"data 1d Integer";
        auto data_1d=CoreUtility::getConfigurationFile()
            .getInputData1DInteger();
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
        qDebug()<<"data 3d Integer";
        auto data_3d=CoreUtility::getConfigurationFile()
            .getInputData3DInteger();
        for (const auto & i:data_3d) {
            qDebug()<<i[0]<<i[1]<<i[2];
        }
    }
}

