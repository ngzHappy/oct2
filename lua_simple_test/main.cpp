#include <QtWidgets/qapplication.h>
#include <QtWidgets/qwidget.h>
#include <core_utility.hpp>
#include <lua/lua.hpp>
#include <iostream>
#include <exception>
#include <OpenCVException.hpp>

int main(int argc, char *argv[])try
{
    QApplication app(argc, argv);

    QWidget * widget = new QWidget;
    widget->setAttribute( Qt::WA_DeleteOnClose );
    widget->show();

    auto _L = LuaUtility::createLuaState();
    lua_State * L=_L.get();
    luaL_dostring(L,"a={1,2,3}");
    luaL_dostring(L,"utility.showTable(\"a\",a)");
    luaL_dostring(L,"return a[1]");
    std::cout <<std::boolalpha<< bool(lua_isnumber(L,-1))<<std::endl;

    auto * thread_= lua_newthread(L);
    lua_pushboolean(thread_,false);

    return app.exec();

}
catch (const cv::Exception & e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}
catch (const std::exception & e) {
    std::cout<<e.what()<<std::endl;
    return -10;
}
catch (...) {
    std::cout<<"unknow exception @ main"<<std::endl;
    return -99999;
}




