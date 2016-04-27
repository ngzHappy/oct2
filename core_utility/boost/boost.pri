INCLUDEPATH += $$PWD
HEADERS += $$PWD/PartBoost.hpp

DEFINES += BOOST_HAS_TR1
DEFINES += BOOST_SP_USE_STD_ATOMIC
DEFINES += BOOST_ALL_NO_LIB
#DEFINES += BOOST_FILESYSTEM_DYN_LINK

linux-g++*{
QMAKE_CXXFLAGS+=-Wno-ignored-qualifiers
QMAKE_CXXFLAGS+=-Wno-deprecated-declarations
}

win32-g++*{
QMAKE_CXXFLAGS+=-Wno-ignored-qualifiers
QMAKE_CXXFLAGS+=-Wno-deprecated-declarations
}

SOURCES += $$PWD/libs/boost_codecvt_error_category.cpp
SOURCES += $$PWD/libs/boost_error_code.cpp
SOURCES += $$PWD/libs/boost_operations.cpp
SOURCES += $$PWD/libs/boost_path.cpp
SOURCES += $$PWD/libs/boost_path_traits.cpp
SOURCES += $$PWD/libs/boost_portability.cpp
SOURCES += $$PWD/libs/boost_unique_path.cpp
SOURCES += $$PWD/libs/boost_utf8_codecvt_facet.cpp
SOURCES += $$PWD/libs/boost_windows_file_codecvt.cpp


