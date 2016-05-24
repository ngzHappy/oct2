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
class Get {
public:
    using type=std::tuple<void *>;
};

template<typename _T_>
class Get<_T_,void_t_cxx17<typename std::remove_pointer_t<_T_>::super_type_tuple>> {
public:
    using type=typename std::remove_pointer_t<_T_>::super_type_tuple;
};

template<typename _T_=void>
std::tuple<void*> cat(const std::tuple<void*>&);
template<typename ... _T_>
auto cat(const std::tuple<_T_...>&_v_)/*
返回类型的递归推导在某些编译器下是失败的
因而不能写成->decltype( std::tuple_cat(_v_,cat( std::declval<typename Get<_T_>::type>() )... ))
*/ {
    throw nullptr/*必须保证此函数不在运行时运行*/;
    using ans_type_cat=
        decltype(std::tuple_cat(_v_,
            cat(std::declval<typename Get<_T_>::type>())...));
    return ans_type_cat{}/*return declval<ans_type_cat>()在某些编译器下是失败的*/;
}

template<typename _Element_,typename _T0_,typename ... _T_>
class HasElementHelp {
public:
    enum {
        value=(std::is_same<_T0_,_Element_>::value)?1:
        HasElementHelp<_Element_,_T_...>::value
    };
};

template<typename _Element_,typename _T0_>
class HasElementHelp<_Element_,_T0_> {
public:
    enum { value=std::is_same<_T0_,_Element_>::value };
};

/*tuple_uniqe*/
template<typename _T_>
std::tuple<_T_> uniqe_help(const std::tuple<_T_>&);
template<typename ... _T_,typename _U_>
auto uniqe_help(const std::tuple<_T_...>&,const _U_&)->std::conditional_t<
    bool(HasElementHelp<_U_,_T_...>::value),
    std::tuple<_T_...>,std::tuple<_T_...,_U_>
>;

template<
    typename _Ans_,
    typename _Input_,
    std::size_t _I_,
    bool endl_=!(_I_<(std::tuple_size<_Input_>::value))>
    class UniqueItem {
    public:
        typedef _Ans_ type;
};

template<
    typename _Ans_,
    typename _Input_,
    std::size_t _I_>
    class UniqueItem<_Ans_,_Input_,_I_,false> {
    using current_element=std::tuple_element_t<_I_,_Input_>;
    using ans_type=decltype(uniqe_help(std::declval<_Ans_>(),
        std::declval<current_element>()));
    public:
        using type=typename UniqueItem<ans_type,_Input_,(1+_I_)>::type;
};

/*tuple_remove*/

}/*tuple_tree_*/
}/*__private*/

template<typename _T_>
class SuperTypeTuple {
private:
    using type_tuple___=typename __private::tuple_tree_::Get<_T_*>::type;
    using ans_type_tuple_=decltype(
        __private::tuple_tree_::cat(std::declval<type_tuple___>())
        );
    using ans_unique_type_=typename __private::tuple_tree_::UniqueItem<
        std::tuple<void *>,
        std::remove_reference_t<ans_type_tuple_>,0>::type;
public:
    using type=std::remove_reference_t<ans_type_tuple_>;
    using unique_type=std::remove_reference_t<ans_unique_type_>;
};

#endif



