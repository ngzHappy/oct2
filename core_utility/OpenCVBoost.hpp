#if !defined(_CCT_BOOST__OPENCV__HPP__0x100)
#define _CCT_BOOST__OPENCV__HPP__0x100() 100

/*
 * 这是boost的一个子集
 * bcp "boost/PartBoost.hpp" "./boost" ....
*/

/*
//change
boost/smart_ptr/detail/lightweight_mutex.hpp

#ifndef BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_MUTEX_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_MUTEX_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <mutex>

namespace boost
{

namespace detail
{

class lightweight_mutex :std::recursive_mutex{
typedef std::recursive_mutex parent_type;
public:
using parent_type::parent_type;
typedef std::unique_lock<lightweight_mutex> scoped_lock;
};

}

}

#endif // #ifndef BOOST_SMART_PTR_DETAIL_LIGHTWEIGHT_MUTEX_HPP_INCLUDED

*/

/*
//change
boost/pool/detail/mutex.hpp

#ifndef BOOST_POOL_MUTEX_HPP
#define BOOST_POOL_MUTEX_HPP

#include <mutex>

namespace boost{
namespace details{
namespace pool{

typedef std::recursive_mutex default_mutex;


} // namespace pool
} // namespace details
} // namespace boost

#endif


*/

/*
//change
"boost\format\alt_sstream_impl.hpp to utf8 with bom
*/

/*
#define BOOST_ALL_NO_LIB
#include <libs/system/src/error_code.cpp>
#include <libs/filesystem/src/codecvt_error_category.cpp>
#include <libs/filesystem/src/operations.cpp>
#include <libs/filesystem/src/path_traits.cpp>
#include <libs/filesystem/src/path.cpp>
#include <libs/filesystem/src/portability.cpp>
#include <libs/filesystem/src/unique_path.cpp>
#include <libs/filesystem/src/utf8_codecvt_facet.cpp>
#include <libs/filesystem/src/windows_file_codecvt.cpp>
#include <boost/filesystem.hpp>
*/

#include "boost/PartBoost.hpp"

/*
1. 命令行进入下载的boost包的根目录
2. bootstrap.bat，得到bjam.exe
3. bjam tools/bcp，在dist\bin目录下会得到bcp.exe
使用bcp工具就可以分离出想要的文件了，例如
dist\bin\bcp shared_ptr.hpp c:\boostX
*/

/*
 * demo
 * bcp "C:/Temp\ffjjj\otestnew\OpenCVTestNew\core_utility\boost\PartBoost.hpp" "C:/Temp\ffjjj\otestnew\OpenCVTestNew\core_utility\boost"
*/



#endif

