#ifndef PRAGMA_ONCE__SuperTypeTuple_HPP__
#define PRAGMA_ONCE__SuperTypeTuple_HPP__

#include <tuple>
#include <memory>
#include <type_traits>

namespace __private {
namespace tuple_tree_ {

/*super_type_tuple*/
template<typename ...> using void_t_cxx17=void;

template<typename _T_,typename _U_=void>
class Get{public:
    using type=std::tuple<void *>;
};

template<typename _T_>
class Get<_T_,void_t_cxx17<typename std::remove_pointer_t<_T_>::super_type_tuple>>{
public:
    using type=typename std::remove_pointer_t<_T_>::super_type_tuple ;
};

template<typename _T_=void>
std::tuple<void*> cat(const std::tuple<void*>&);
template<typename ... _T_>
auto cat(const std::tuple<_T_...>&_v_)/*
返回类型的递归推导在某些编译器下是失败的
因而不能写成->decltype( std::tuple_cat(_v_,cat( std::declval<typename Get<_T_>::type>() )... ))
*/{
    throw nullptr/*必须保证此函数不在运行时运行*/;
    using ans_type_cat=
        decltype( std::tuple_cat(_v_,
        cat( std::declval<typename Get<_T_>::type>() )... ));
    return ans_type_cat{}/*return declval<ans_type_cat>()在某些编译器下是失败的*/;
}

}/*tuple_tree_*/
}/*__private*/

template<typename _T_>
class SuperTypeTuple {
private:
    using type_tuple___=typename __private::tuple_tree_::Get<_T_*>::type;
    using ans_type_tuple_=decltype(
        __private::tuple_tree_::cat(std::declval<type_tuple___>()));
public:
    using type=std::remove_reference_t<ans_type_tuple_>;
};

#endif



