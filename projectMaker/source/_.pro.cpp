//_replace_first_window_replace_
//_replace_$$PWD/../core_utility/core_utility.pri_replace_
//_replace_$$PWD/../core_utility/opencv3.pri_replace_
//_replace_$$PWD/first_window.lua_replace_

const char *_pro = u8R"=_____=(##pro

QT += gui
QT += core
QT += widgets
QT += charts

CONFIG += c++14

TARGET = _replace_first_window_replace_
CONFIG += console


TEMPLATE = app

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/MainWindow.cpp
SOURCES += $$PWD/OpenCVWindowDetail.cpp
SOURCES += $$PWD/run.cpp

HEADERS += $$PWD/MainWindow.hpp
HEADERS += $$PWD/OpenCVWindowDetail.hpp

DEFINES += BUILD_PATH_=\\\"$$PWD\\\"

include( _replace_$$PWD/../core_utility/core_utility.pri_replace_ )
include( _replace_$$PWD/../core_utility/opencv3.pri_replace_ )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lcore_utilityd
}else{
LIBS += -L$$OUTPWD -lcore_utility
}

DISTFILES += _replace_$$PWD/first_window.lua_replace_

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}

)=_____=";
