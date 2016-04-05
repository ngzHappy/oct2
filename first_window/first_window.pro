QT += gui
QT += core
QT += widgets
QT += charts

CONFIG += c++14

TARGET = first_window
CONFIG += console


TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    OpenCVWindowDetail.cpp \
    run.cpp

HEADERS += \
    MainWindow.hpp \
    OpenCVWindowDetail.hpp

DEFINES += BUILD_PATH_=\\\"$$PWD\\\"

include( $$PWD/../core_utility/core_utility.pri )
include( $$PWD/../core_utility/opencv3.pri )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lcore_utilityd
}else{
LIBS += -L$$OUTPWD -lcore_utility
}

DISTFILES += $$PWD/first_window.lua

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}
