QT += gui
QT += core
QT += widgets
QT += charts


TARGET = lua
CONFIG += console


TEMPLATE = app

SOURCES += $$PWD/../core_utility/lua/lua_lua.cpp

include( $$PWD/../core_utility/core_utility.pri )
include( $$PWD/../core_utility/opencv3.pri )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lcore_utilityd
}else{
LIBS += -L$$OUTPWD -lcore_utility
}

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}
