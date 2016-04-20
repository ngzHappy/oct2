INCLUDEPATH += $$PWD

DEFINES += BOOST_HAS_TR1
DEFINES += BOOST_SP_USE_STD_ATOMIC


linux-g++*{
QMAKE_CXXFLAGS+=-Wno-ignored-qualifiers
}

win32-g++*{
QMAKE_CXXFLAGS+=-Wno-ignored-qualifiers
}


