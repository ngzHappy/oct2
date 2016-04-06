/*main.cpp*/
#include "MainWindow.hpp"
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <iostream>

extern void run(OpenCVWindow * window) ;

/*命令行解析器*/
class CommandLineParser : public QCommandLineParser {
public:
    CommandLineParser() {
        this->addVersionOption();
        this->addHelpOption();
        this->addOption(QCommandLineOption("lua","lua configure file",QString(),
            "opencv_rect.lua"));
    }
};

int main(int argc,char ** argv) {
    /*设置本地编码*/
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));

    /*初始化应用程序*/
    QApplication app(argc,argv);

    {
        /*解析命令行*/
        CommandLineParser parser;
        parser.process(app);

        /*全局配置文件*/
        const QByteArray lua_file_name_=parser.value("lua").toLocal8Bit();
        OpenCVApplicationConfigurationFile configure(
            app.applicationFilePath().toLocal8Bit(),
            BUILD_PATH_,lua_file_name_.constData());

    }

    /*设置图片搜索目录*/
    {
        QDir::addSearchPath("images",app.applicationDirPath()+"/Images");
        QDir::addSearchPath("images",BUILD_PATH_);
        QDir::addSearchPath("images",QDir::cleanPath(BUILD_PATH_"/../../Images"));
    }

    MainWindow * window=new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    run(window->getOpenCVWindow());
    std::cout.flush();
    window->show();

    return app.exec();

}

