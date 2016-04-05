QT -= core
QT -= gui

CONFIG += c++14

TARGET = projectMaker
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += $$PWD/ArgvPack.hpp

SOURCES += main.cpp \
    ArgvPack.cpp \
    run.cpp \
    source/_.lua.cpp \
    source/_.pro.cpp \
    source/_main.cpp \
    source/_MainWindow.cpp \
    source/_OpenCVWindowDetail.cpp \
    source/_run.cpp \
    source/_MainWindow.hpp.cpp \
    source/_OpenCVWindowDetail.hpp.cpp

include( $$PWD/../core_utility/core_utility.pri )
DESTDIR = $$OUTPWD

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}

