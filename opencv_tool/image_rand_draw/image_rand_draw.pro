CONFIG += c++14
CONFIG += console

QT += core gui
QT += widgets
QT += concurrent
QT += qml
QT += quick

TARGET = image_rand_draw
TEMPLATE = app


SOURCES += main.cpp \
    MainWindow.cpp

HEADERS  += \
    MainWindow.hpp

include( $$PWD/../../core_utility/core_utility.pri )
include( $$PWD/../../core_utility/opencv3.pri )
DESTDIR = $$OUTPWD

RESOURCES += \
    qmlSource.qrc


