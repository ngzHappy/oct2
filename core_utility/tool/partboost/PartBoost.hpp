#include "boost/utility.hpp"
#include "boost/optional.hpp"
#include "boost/signals2.hpp"
#include "boost/smart_ptr.hpp"
#include "boost/pool/pool.hpp"
#include "boost/circular_buffer.hpp"
#include "boost/geometry/index/rtree.hpp"
#include "boost/geometry.hpp"
#include "boost/ptr_container/ptr_container.hpp"
#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/asio.hpp"

/*********

linux-g++*{
QMAKE_CXXFLAGS+=-Wno-ignored-qualifiers
QMAKE_CXXFLAGS+=-Wno-deprecated-declarations
}

win32-g++*{
QMAKE_CXXFLAGS+=-Wno-ignored-qualifiers
QMAKE_CXXFLAGS+=-Wno-deprecated-declarations
}

win32:{
#boost filesystem
LIBS += -lAdvapi32
DEFINES *=_WIN32_WINNT=0x0501
}

win32-g++*{
LIBS += -lws2_32
LIBS += -lwsock32
}

BOOST_CHRONO_DYN_LINK
BOOST_DATE_TIME_DYN_LINK
BOOST_FILESYSTEM_DYN_LINK
BOOST_REGEX_DYN_LINK
BOOST_SYSTEM_DYN_LINK
_SCL_SECURE_NO_WARNINGS
*********/


