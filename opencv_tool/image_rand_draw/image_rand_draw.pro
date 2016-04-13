CONFIG += c++14

QT += core gui
QT += widgets
QT += concurrent

TARGET = image_rand_draw
TEMPLATE = app


SOURCES += main.cpp \
    MainWindow.cpp

HEADERS  += \
    MainWindow.hpp

include( $$PWD/../../core_utility/core_utility.pri )
DESTDIR = $$OUTPWD


