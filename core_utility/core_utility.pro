CONFIG += c++14

QT += gui
QT += core
QT += widgets
QT += charts

QT += core_private
QT += gui_private
QT += widgets_private
QT += charts_private

CONFIG(debug,debug|release){
TARGET = core_utilityd
}else{
TARGET = core_utility
}

TEMPLATE = lib

DEFINES += CORE_UTILITY_LIBRARY
DEFINES += QTUTILITY_LIBRARY
DEFINES += QUAZIP_BUILD
DEFINES += LUA_BUILD_AS_DLL
win32{
}else{
DEFINES += LUA_USE_LINUX
}

SOURCES += $$PWD/source/core_utility.cpp
SOURCES += $$PWD/source/lua_utility.cpp
SOURCES += $$PWD/source/opencv_application_configuration_file.cpp
SOURCES += $$PWD/source/OpenCVHistItem.cpp
SOURCES += $$PWD/source/OpenCVImageItem.cpp
SOURCES += $$PWD/source/OpenCVItem.cpp
SOURCES += $$PWD/source/OpenCVScene.cpp
SOURCES += $$PWD/source/OpenCVWindow.cpp
SOURCES += $$PWD/source/OpenCVStyle.cpp
SOURCES += $$PWD/source/OpenCVScatterItem.cpp
SOURCES += $$PWD/source/OpenCVLineSeriesItem.cpp
SOURCES += $$PWD/source/OpenCVUtility.cpp
SOURCES += $$PWD/source/OpenCVMatProxyAllocator.cpp

HEADERS += $$PWD/private/_core_utility_prebuild.hpp
HEADERS += $$PWD/core_utility.hpp
HEADERS += $$PWD/OpenCVMatProxyAllocator.hpp
HEADERS += $$PWD/getxy.hpp
HEADERS += $$PWD/core_utility_global.hpp
HEADERS += $$PWD/opencv_application_configuration_file.hpp
HEADERS += $$PWD/ReadOnly.hpp
HEADERS += $$PWD/OpenCVWindow.hpp
HEADERS += $$PWD/OpenCVScene.hpp
HEADERS += $$PWD/OpenCVItem.hpp
HEADERS += $$PWD/OpenCVImageItem.hpp
HEADERS += $$PWD/OpenCVHistItem.hpp
HEADERS += $$PWD/OpenCVStyle.hpp
HEADERS += $$PWD/OpenCVScatterItem.hpp
HEADERS += $$PWD/OpenCVLineSeriesItem.hpp
HEADERS += $$PWD/OpenCVUtility.hpp
HEADERS += $$PWD/OpenCVUserDataAllocator.hpp

include($$PWD/core_utility.pri)
include($$PWD/opencv3.pri)
include($$PWD/quazip/quazip.pri)
include($$PWD/lua/lua.pri)
DESTDIR = $$OUTPWD

DISTFILES += $$PWD/../Images/000000.jpg
DISTFILES += $$PWD/../Images/000001.jpg
DISTFILES += $$PWD/../Images/000002.jpg
DISTFILES += $$PWD/../Images/000003.jpg
DISTFILES += $$PWD/../Images/000006.jpg
DISTFILES += $$PWD/../Images/000007.jpg
DISTFILES += $$PWD/../Images/000004.png
DISTFILES += $$PWD/../Images/000005.png
DISTFILES += $$PWD/../Images/000006.jpg
DISTFILES += $$PWD/../Images/000007.jpg
DISTFILES += $$PWD/../Images/000008.jpg
DISTFILES += $$PWD/../Images/000009.pbm

RESOURCES += imageResource.qrc

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}

CONFIG += precompile_header
PRECOMPILED_HEADER  = $$PWD/private/_core_utility_prebuild.hpp

