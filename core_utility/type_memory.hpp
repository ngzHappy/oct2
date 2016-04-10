#if !defined(__TYPE__MEMORY_HPP_)
#define __TYPE__MEMORY_HPP_() 1

#include <memory>
#include <type_traits>
namespace cct {

template<
    typename _T_,
    typename _D_
>
inline auto wrap_unique(_T_ * _data_,_D_&&_deleter)->std::unique_ptr<_T_,std::remove_reference_t<_D_>> {
    return std::unique_ptr<_T_,std::remove_reference_t<_D_>>{
        _data_,std::forward<_D_>(_deleter)};
}

template<
    typename _T_,
    typename _D_
>
inline auto wrap_shared_ptr(_T_ * _data_,_D_&&_deleter)->std::shared_ptr<_T_> {
    return std::shared_ptr<_T_>(
        wrap_unique(_data_,std::forward<_D_>(_deleter)));
}

typedef void(*deleter_uniqute_ptr_t)(const void *);
template<
    typename _T_,
    typename _U_=std::enable_if_t<!(std::is_array<_T_>::value)>,
    typename ... Args
>
inline auto make_unique(Args && ... args)->std::unique_ptr<_T_,deleter_uniqute_ptr_t> {
    return std::unique_ptr<_T_,deleter_uniqute_ptr_t>(
        new _T_(std::forward<Args>(args)...),
        [](const void * _d) {delete ((_T_ *)(_d)); }
    );
}

template<
    typename _T_,
    typename _U_=std::enable_if_t<!(std::is_array<_T_>::value)>,
    typename ... Args
>
inline auto instance_unique(Args && ... args)->std::unique_ptr<_T_,deleter_uniqute_ptr_t> {
    return std::unique_ptr<_T_,deleter_uniqute_ptr_t>(
        new _T_{ std::forward<Args>(args)... },
        [](const void * _d) {delete ((_T_ *)(_d)); }
    );
}

template<
    typename _T_,
    typename _U_=std::enable_if_t<!(std::is_array<_T_>::value)>,
    typename ... Args
>
inline auto make_shared_ptr(Args&&...args)->std::shared_ptr<_T_> {
    return std::shared_ptr<_T_>(make_unique<_T_>(std::forward<Args>(args)...));
}

template<
    typename _T_,
    typename _U_=std::enable_if_t<!(std::is_array<_T_>::value)>,
    typename ... Args
>
inline auto instance_shared_ptr(Args&&...args)->std::shared_ptr<_T_> {
    return std::shared_ptr<_T_>(instance_unique<_T_>(std::forward<Args>(args)...));
}

template<
    typename _T_,
    typename _U_=std::enable_if_t<!(std::is_array<_T_>::value)>,
    typename ... Args,
    typename Deleter
>
inline auto make_shared_ptr_add_deleter(
    Deleter && deleter,
    Args&&...args
    ) ->std::shared_ptr<_T_> {
    typedef std::remove_const_t<std::remove_reference_t<Deleter>> Deleter_;
    Deleter_ deleter_0_{ std::forward<Deleter>(deleter) }/*create a copy*/;
    auto data_=make_unique<_T_>(std::forward<Args>(args)...)/*create data*/;
    deleter_uniqute_ptr_t deleter_1_=data_.get_deleter();
    auto deleter_=[deleter_1_=std::move(deleter_1_),
        deleter_0_=std::move(deleter_0_)
    ](_T_ * _data) {deleter_0_(_data); deleter_1_(_data); }/*create delete function*/;
    return std::shared_ptr<_T_>(
        data_.release(),
        std::move(deleter_)
        );
}

template<
    typename _T_,
    typename _U_=std::enable_if_t<!(std::is_array<_T_>::value)>,
    typename ... Args,
    typename Deleter
>
inline auto instance_shared_ptr_add_deleter(
    Deleter && deleter,
    Args&&...args
    ) ->std::shared_ptr<_T_> {
    typedef std::remove_const_t<std::remove_reference_t<Deleter>> Deleter_;
    Deleter_ deleter_0_{ std::forward<Deleter>(deleter) }/*create a copy*/;
    auto data_=instance_unique<_T_>(std::forward<Args>(args)...)/*create data*/;
    deleter_uniqute_ptr_t deleter_1_=data_.get_deleter();
    auto deleter_=[deleter_1_=std::move(deleter_1_),
        deleter_0_=std::move(deleter_0_)
    ](_T_ * _data) {deleter_0_(_data); deleter_1_(_data); }/*create delete function*/;
    return std::shared_ptr<_T_>(
        data_.release(),
        std::move(deleter_)
        );
}
}/*~namespace */

#endif
