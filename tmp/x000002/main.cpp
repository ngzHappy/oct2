/*main.cpp "x000002"  */
#include "MainWindow.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qcommandlineparser.h>
#include <QtCore/qcommandlineoption.h>
#include <QtCore/qtextcodec.h>
#include <QtCore/qdir.h>
#include <opencv_application_configuration_file.hpp>
#include <iostream>
#include <OpenCVException.hpp>
#include <lua/lua.hpp>
#include <string>

using namespace std::string_literals;

namespace x000002{
extern void run(OpenCVWindow * window) ;
}

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

int main(int argc,char ** argv) try{
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
    window->show();
    x000002::run(window->getOpenCVWindow());
    std::cout.flush();

    {
        std::vector<char> buffer;

        {
            auto*L=luaL_newstate();
            luaL_openlibs(L);

            //luaL_dostring(L,u8R"(print("Hellow Word!"))");

            auto writer=[](lua_State *,
                const void* p,
                size_t sz,
                void* buffer)->int {
                auto * buf=reinterpret_cast<std::vector<char>*>(buffer);
                const char * data_=reinterpret_cast<const char *>(p);
                for (size_t i=0; i<sz; ++i) {
                    buf->push_back(*data_);
                    ++data_;
                }
                return 0;
            };

            auto testString=u8R"( return function() print("Hellow Word!") end )"s;
            luaL_loadbuffer(L,testString.c_str(),testString.size(),"?");
            lua_pcall(L,0,LUA_MULTRET,-1);
            //lua_pushvalue(L,-1);
            //luaL_dostring(L,u8R"(foo())");
            //luaL_dostring(L,testString.c_str());
            //lua_getglobal(L,"foo");
            std::cout<<std::boolalpha<<lua_isfunction(L,-1)<<std::endl;
            lua_dump(L,writer,&buffer,true);

            std::cout<<buffer.size()<<std::endl;
            lua_close(L);

        }

        {
            auto*L=luaL_newstate();
            luaL_openlibs(L);

            luaL_loadbuffer(L,buffer.data(),buffer.size(),"?");
            //lua_pcall(L,0,LUA_MULTRET,-1);
            //lua_pushvalue(L,-1);
            //luaL_dostring(L,u8R"(foo())");
            std::cout<<lua_isfunction(L,-1)<<std::endl;
            lua_pcall(L,0,LUA_MULTRET,-1);

            lua_close(L);
        }

    }
    return app.exec();

}
catch (const cv::Exception & e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
    return -1;
}
catch (const std::exception & e) {
    std::cout<<e.what()<<std::endl;
    return -10;
}
catch (...) {
    std::cout<<"unknow exception @ main"<<std::endl;
    return -99999;
}

