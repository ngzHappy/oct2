##pro

QT += gui
QT += core
QT += widgets
QT += charts

CONFIG += c++14

TARGET = opencv_fitLine
CONFIG += console


TEMPLATE = app

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/MainWindow.cpp
SOURCES += $$PWD/OpenCVWindowDetail.cpp
SOURCES += opencv_fitLine_run.cpp

HEADERS += $$PWD/MainWindow.hpp
HEADERS += $$PWD/OpenCVWindowDetail.hpp

DEFINES += APP_NAME_=\\\"$$TARGET\\\"
DEFINES += BUILD_PATH_=\\\"$$PWD\\\"

include( $$PWD/../../core_utility/core_utility.pri )
include( $$PWD/../../core_utility/opencv3.pri )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lcore_utilityd
}else{
LIBS += -L$$OUTPWD -lcore_utility
}

DISTFILES += $$PWD/opencv_fitLine.lua
DISTFILES += $$PWD/private/opencv_fitLine_run_exception.cpp

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}

HEADERS += $$PWD/private/pre_build.hpp
HEADERS += $$PWD/private/msvc_pre_build.hpp
CONFIG += precompile_header
win32-msvc*{
PRECOMPILED_HEADER  += $$PWD/private/msvc_pre_build.hpp
}else{
PRECOMPILED_HEADER  += $$PWD/private/pre_build.hpp
}

