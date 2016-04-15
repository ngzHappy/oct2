/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
#include <QtCore/qdebug.h>
#include "private/opencv_saveload_run_exception.cpp"
namespace opencv_saveload{
extern void run(OpenCVWindow * window) try{

    /*格式化输出*/
    {
        cv::Mat mat(1,2,CV_32FC1);
        mat.at<float>(0,1)=1;mat.at<float>(0,0)=5;
        std::cout<<cv::format(mat,cv::Formatter::FMT_PYTHON)<<std::endl;
    }

    /*数据XML保存读入*/
    {
        const QByteArray fileName=QDir::cleanPath(qApp->applicationDirPath()).toLocal8Bit()+"/core_mat_saveload_test.xml";
        QImage image0("images:000000");
        window->insertImage(image0)->setWindowTitle(u8R"(原始图片)"_qs);

        auto imageMat=OpenCVUtility::tryRead(image0);
        {
            /*提高亮度*/
            imageMat*=1.3;
            /*保存图片*/
            {
                cv::FileStorage file(
                    cv::String(fileName.constData(),fileName.size()),
                    cv::FileStorage::WRITE
                    );
                file<<"images_000000"<<imageMat;
            }
            /*重新载入图片*/
            {
                cv::FileStorage file(
                    cv::String(fileName.constData(),fileName.size()),
                    cv::FileStorage::READ
                    );
                file["images_000000"]>>imageMat;
            }
        }

        window->insertImage(OpenCVUtility::tryRead(imageMat))\
            ->setWindowTitle(u8R"(读入图片)"_qs);
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}


}
