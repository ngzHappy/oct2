//_replace_first_window.lua_replace_
//_replace_/../Images_replace_

const char *_main_cpp = u8R"=_____=(/*main.cpp _replace_first_window.lua_replace_  */
#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qcommandlineparser.h>
#include <QtCore/qcommandlineoption.h>
#include <QtCore/qtextcodec.h>
#include <QtCore/qdir.h>
#include <opencv_application_configuration_file.hpp>
#include <iostream>

extern void run(OpenCVWindow * window) ;

/*命令行解析器*/
class CommandLineParser : public QCommandLineParser {
public:
    CommandLineParser() {
        auto & parser=*this;
        parser.addVersionOption();
        parser.addHelpOption();
        const QCommandLineOption op(
            { "l","lua" },
            u8"lua configure file application.input_images application.input_data_2d"_qs,
            "lua",
            APP_NAME_);
        parser.addOption(op);
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
        QDir::addSearchPath("images",QDir::cleanPath(BUILD_PATH_"_replace_/../Images_replace_"));
    }

    MainWindow * window=new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
    run(window->getOpenCVWindow());
    std::cout.flush();

    return app.exec();

}

)=_____=";
