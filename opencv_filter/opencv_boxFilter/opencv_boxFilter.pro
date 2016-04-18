##pro

QT += gui
QT += core
QT += widgets
QT += charts


TARGET = opencv_boxFilter
CONFIG += console


TEMPLATE = app

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/MainWindow.cpp
SOURCES += $$PWD/OpenCVWindowDetail.cpp
SOURCES += opencv_boxFilter_run.cpp

HEADERS += $$PWD/MainWindow.hpp
HEADERS += $$PWD/OpenCVWindowDetail.hpp

DEFINES += APP_NAME_=\\\"$$TARGET\\\"
DEFINES += BUILD_PATH_=\\\"$$PWD\\\"
DISTFILES += $$PWD/private/opencv_boxFilter_run_exception.cpp

include( $$PWD/../../core_utility/core_utility.pri )
include( $$PWD/../../core_utility/opencv3.pri )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lcore_utilityd
}else{
LIBS += -L$$OUTPWD -lcore_utility
}

DISTFILES += $$PWD/opencv_boxFilter.lua

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

