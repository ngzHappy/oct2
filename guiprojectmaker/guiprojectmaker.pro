
QT += core gui
QT += widgets

TARGET = guiprojectmaker
TEMPLATE = app

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/MainWindow.cpp
SOURCES += $$PWD/../projectMaker/ArgvPack.cpp
SOURCES += $$PWD/../projectMaker/run.cpp
SOURCES += $$PWD/../projectMaker/source/_.lua.cpp
SOURCES += $$PWD/../projectMaker/source/_.pro.cpp
SOURCES += $$PWD/../projectMaker/source/_main.cpp
SOURCES += $$PWD/../projectMaker/source/_MainWindow.cpp
SOURCES += $$PWD/../projectMaker/source/_MainWindow.hpp.cpp
SOURCES += $$PWD/../projectMaker/source/_msvc_pre_build.hpp.cpp
SOURCES += $$PWD/../projectMaker/source/_OpenCVWindowDetail.cpp
SOURCES += $$PWD/../projectMaker/source/_OpenCVWindowDetail.hpp.cpp
SOURCES += $$PWD/../projectMaker/source/_pre_build.hpp.cpp
SOURCES += $$PWD/../projectMaker/source/_run.cpp
SOURCES += $$PWD/../projectMaker/source/_run_exception.cpp

HEADERS  += $$PWD/MainWindow.hpp
HEADERS  += $$PWD/../projectMaker/ArgvPack.hpp

FORMS    += $$PWD/MainWindow.ui

include( $$PWD/../core_utility/core_utility.pri )
DESTDIR = $$OUTPWD

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}



