/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
#include <QtCore/qdebug.h>
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
catch (const cv::Exception &) {
    /*std::quick_exit(-1);*/
}
