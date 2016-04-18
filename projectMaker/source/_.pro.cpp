//_replace_first_window_replace_
//_replace_$$PWD/../core_utility/core_utility.pri_replace_
//_replace_$$PWD/../core_utility/opencv3.pri_replace_
//_replace_$$PWD/first_window.lua_replace_
//$$PWD/_replace_run.cpp_replace_
//_replace_simple_pca_run__replace_

const char *_pro = u8R"=_____=(##pro

QT += gui
QT += core
QT += widgets
QT += charts


TARGET = _replace_first_window_replace_
CONFIG += console


TEMPLATE = app

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/MainWindow.cpp
SOURCES += $$PWD/OpenCVWindowDetail.cpp
SOURCES += $$PWD/_replace_run.cpp_replace_

HEADERS += $$PWD/MainWindow.hpp
HEADERS += $$PWD/OpenCVWindowDetail.hpp

DEFINES += APP_NAME_=\\\"$$TARGET\\\"
DEFINES += BUILD_PATH_=\\\"$$PWD\\\"
DISTFILES += $$PWD/private/_replace_simple_pca_run__replace_exception.cpp

include( _replace_$$PWD/../core_utility/core_utility.pri_replace_ )
include( _replace_$$PWD/../core_utility/opencv3.pri_replace_ )
DESTDIR = $$OUTPWD
CONFIG(debug,debug|release){
LIBS += -L$$OUTPWD -lcore_utilityd
}else{
LIBS += -L$$OUTPWD -lcore_utility
}

DISTFILES += _replace_$$PWD/first_window.lua_replace_

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

)=_____=";
