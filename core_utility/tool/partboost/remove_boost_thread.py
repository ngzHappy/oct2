
import os
import sys

def get_full_fileName(path_,name_):
    return os.path.join(path_,name_)
    pass

def user_configure_change(boostDirName):
    fileName=get_full_fileName(boostDirName,"boost/config/user.hpp")
    with open(fileName,"w") as fp:
        fp.write("""
#ifndef BOOST_HAS_TR1
#define BOOST_HAS_TR1
#endif

#ifndef BOOST_SP_USE_STD_ATOMIC
#define BOOST_SP_USE_STD_ATOMIC
#endif

#ifndef BOOST_ALL_NO_LIB
#define BOOST_ALL_NO_LIB
#endif

""")
    pass

def shared_ptr_change(boostDirName):
    fileName=get_full_fileName(boostDirName,"boost/smart_ptr/detail/lightweight_mutex.hpp")
    with open(fileName,"w") as fp:
        fp.write("""
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

""")
    pass

def pool_change(boostDirName):
    fileName=get_full_fileName(boostDirName,"boost/pool/detail/mutex.hpp")
    with open(fileName,"w") as fp:
        fp.write("""
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

""")
    pass

def remove_boost_thread(boostDirName):
    user_configure_change(boostDirName);
    shared_ptr_change(boostDirName);
    pool_change(boostDirName);
    pass

if __name__=="__main__":
    if len(sys.argv)>1:
        remove_boost_thread(sys.argv[1])
    else:
        remove_boost_thread(os.getcwd())
