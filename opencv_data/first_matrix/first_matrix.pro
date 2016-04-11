##pro

QT += gui
QT += core
QT += widgets
QT += charts

CONFIG += c++14

TARGET = first_matrix
CONFIG += console


TEMPLATE = app

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/MainWindow.cpp
SOURCES += $$PWD/OpenCVWindowDetail.cpp
SOURCES += $$PWD/first_matrix_run.cpp

HEADERS += $$PWD/MainWindow.hpp
HEADERS += $$PWD/OpenCVWindowDetail.hpp

DEFINES += BUILD_PATH_=\\\"$$PWD\\\"
DEFINES += APP_NAME_=\\\"$$TARGET\\\"

include( $$PWD/../../core_utility/core_utility.pri )
include( $$PWD/../../core_utility/opencv3.pri )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lcore_utilityd
}else{
LIBS += -L$$OUTPWD -lcore_utility
}

DISTFILES += $$PWD/first_matrix.lua
DISTFILES += $$PWD/first_matrix.PNG
DISTFILES += $$PWD/private/first_matrix_run_exception.cpp

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

