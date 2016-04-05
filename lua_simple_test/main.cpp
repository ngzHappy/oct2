#include <QtWidgets/qapplication.h>
#include <QtWidgets/qwidget.h>
#include <core_utility.hpp>
#include <iostream>

int main(int argc, char *argv[])
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

    return app.exec();

}




