#if  !defined(_0_READONLY_HPP)
#define _0_READONLY_HPP() 1

//#include "QtUtility.hpp"

namespace {
namespace __header{
namespace __cct {
namespace __private {

class __IsShared {};

template<typename _U_>
__IsShared * __type(const std::shared_ptr<_U_> &);

template<typename _U_>
__IsShared * __type(const QSharedPointer<_U_> &);

template<typename _U_=void>
void * __type(...);

template<
    typename _T_,
    int type_shared_=int(std::is_same<__IsShared *,decltype(__type(std::declval<_T_>()))>::value)>
class ___IsShared {
public:
    enum { value=1 };
    template<typename _U_>
    static std::add_const_t<_U_> * eval(const std::shared_ptr<_U_> & value_) {
        return value_.get();
    }
    template<typename _U_>
    static std::add_const_t<_U_> * eval(const QSharedPointer<_U_> & value_) {
        return value_.data();
    }
};

template<typename _T_>
class ___IsShared<_T_,0> {
public:
    enum { value=0 };
    typedef std::add_const_t< std::remove_reference_t<_T_> > const_type;
    template<typename _U_>
    static const_type & eval(_U_ & value_) noexcept { return value_; }
};

/*namespace*/
}/*namespace __private*/
}/*namespace __cct*/
}/*namespace __header*/
}/*namespace*/

template<typename _T_  >
inline decltype(auto) readOnly(_T_ & value_) {
    static_assert(false==std::is_reference<_T_>::value,"type should not be & or &&");
    return __header::__cct::__private::___IsShared<_T_>::eval(value_);
}


#endif // READONLY_HPP


