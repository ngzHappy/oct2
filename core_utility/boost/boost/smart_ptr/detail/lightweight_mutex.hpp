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
