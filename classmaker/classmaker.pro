TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
SOURCES += _cpp.cpp
SOURCES += _data.cpp
SOURCES += _function.cpp
SOURCES += _hpp.cpp
SOURCES += run.cpp

include( $$PWD/../core_utility/core_utility.pri )
include( $$PWD/../core_utility/boost/boost.pri )
!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}
DESTDIR = $$OUTPWD

