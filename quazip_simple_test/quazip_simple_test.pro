QT += gui
QT += core
QT += widgets
QT += charts

CONFIG += c++14

TARGET = quazip_simple_test
CONFIG += console


TEMPLATE = app

SOURCES += main.cpp
DEFINES += BUILD_PATH_=\\\"$$PWD\\\"
DEFINES += APP_NAME_=\\\"$$TARGET\\\"

include( $$PWD/../core_utility/core_utility.pri )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lcore_utilityd
}else{
LIBS += -L$$OUTPWD -lcore_utility
}

!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}
