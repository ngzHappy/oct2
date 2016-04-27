INCLUDEPATH += $$PWD

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

SOURCES += $$PWD/libs/codecvt_error_category.cpp
SOURCES += $$PWD/libs/error_code.cpp
SOURCES += $$PWD/libs/operations.cpp
SOURCES += $$PWD/libs/path.cpp
SOURCES += $$PWD/libs/path_traits.cpp
SOURCES += $$PWD/libs/portability.cpp
SOURCES += $$PWD/libs/unique_path.cpp
SOURCES += $$PWD/libs/utf8_codecvt_facet.cpp
SOURCES += $$PWD/libs/windows_file_codecvt.cpp


