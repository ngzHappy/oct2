#ifndef CORE_UTILITY_GLOBAL_HPP
#define CORE_UTILITY_GLOBAL_HPP

#include <QtCore/qglobal.h>

/***********************************/
//动态链接库宏定义
/***********************************/
#if defined(CORE_UTILITY_LIBRARY)
#  define CORE_UTILITYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CORE_UTILITYSHARED_EXPORT Q_DECL_IMPORT
#endif

/***********************************/
//标准库头文件
/***********************************/
#include <ratio>
#include <ctime>
#include <cmath>
#include <memory>
#include <atomic>
#include <thread>
#include <random>
#include <chrono>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <ciso646>
#include <utility>
#include <numeric>
#include <algorithm>
#include <functional>
#include <type_traits>
using namespace std::chrono_literals;/*s ns ms*/

/***********************************/
//标准库字符串相关
/***********************************/
#include <regex>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std::string_literals;/*s*/

template<typename _t_STD_STRINGSTREAM_>
inline std::pair<const char *,std::streamoff>
readAll(const _t_STD_STRINGSTREAM_ & data__) {
    _t_STD_STRINGSTREAM_ & data_=const_cast<_t_STD_STRINGSTREAM_ &>(data__);
    std::pair<const char *,std::streamoff> ans_{ nullptr,0 };
    typedef decltype(data_.rdbuf()) ReaderBuffer___;
    typedef std::remove_reference_t<ReaderBuffer___> ReaderBuffer__;
    typedef std::remove_pointer_t<ReaderBuffer__> ReaderBuffer_;
    typedef std::remove_cv_t<ReaderBuffer_> _ReaderBuffer;
    class RBUF : public _ReaderBuffer {
    public:
        using _ReaderBuffer::egptr;
        using _ReaderBuffer::gptr;
        using _ReaderBuffer::eback;
    };
    const auto read_pos_=data_.tellg();
    RBUF * rbuf_=reinterpret_cast<RBUF *>(data_.rdbuf());
    if (rbuf_==nullptr) { return ans_; }
    ans_.first=rbuf_->eback();
    data_.seekg(0,std::ios::end);
    ans_.second = data_.tellg();
    data_.seekg(read_pos_);
    return ans_;
}

/***********************************/
//protect public 切换宏
/***********************************/
#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

/***********************************/
//基本数据类型定义
/***********************************/

/*cplusplus core type traits*/
namespace cct{
using Double=std::double_t;
using Float=std::float_t;
using Integer=std::int32_t;
using UnsignedInteger=std::uint32_t;
using Boolean=bool;
using Void=void;
}

#if !defined(MACRO_CCT_USING_BASE_TYPE)
#define MACRO_CCT_USING_BASE_TYPE using cct::Double; \
using cct::Float; \
using cct::Integer; \
using cct::UnsignedInteger; \
using cct::Boolean; \
using cct::Void/*;*/
#endif
/***********************************/

#endif // CORE_UTILITY_GLOBAL_HPP
