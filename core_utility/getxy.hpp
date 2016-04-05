#ifndef __GETXY_HPP0x00
#define __GETXY_HPP0x00

#include <type_traits>

template<typename _Type_=double,
    typename _U_,
    typename _TEST_=decltype(static_cast<_Type_>((*std::declval<_U_>()).x())) >
    inline _Type_ getX(_U_ && it_) { return static_cast<_Type_>((*it_).x()); }
template<typename _Type_=double,
    typename _U_,
    typename _TEST_=decltype(static_cast<_Type_>((*std::declval<_U_>()).x)),
    typename _O_=void
>
inline _Type_ getX(_U_ && it_) { return static_cast<_Type_>((*it_).x); }

template<typename _Type_=double,
    typename _U_,
    typename _TEST_=decltype(static_cast<_Type_>((*std::declval<_U_>()).y())) >
    inline _Type_ getY(_U_ && it_) { return static_cast<_Type_>((*it_).y()); }
template<typename _Type_=double,
    typename _U_,
    typename _TEST_=decltype(static_cast<_Type_>((*std::declval<_U_>()).y)),
    typename _O_=void
>
inline _Type_ getY(_U_ && it_) { return static_cast<_Type_>((*it_).y); }


#endif // GETXY_HPP
