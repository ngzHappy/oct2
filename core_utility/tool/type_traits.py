

def get_type_traits():
    return"""/*___SSS___ type traits*/
#ifndef __PRAGMA_ONCE____SSS___HXX_0x00
#define __PRAGMA_ONCE____SSS___HXX_0x00

#include <memory>
#include <cstdlib>
#include <utility>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <algorithm>
#include <functional>
#include <type_traits>

/*zone_namespace_begin*/

class ___SSS___TypeTraits;
class ___SSS___TypeTraits {
public:
    ___SSS___TypeTraits()=default;
public:
    template<typename...>using void_t=void;
    using Size=std::size_t;
    using Integer=std::int32_t;
public:
    template<typename __T__>
    using SharedPointer=std::shared_ptr<__T__>;
    template<typename __T__>
    using WeakPointer=std::weak_ptr<__T__>;
    template<typename __T__>
    using SharedFromThis=std::enable_shared_from_this<__T__>;
    template<typename __T__>
    using sp=SharedPointer<__T__>;
    template<typename __T__>
    using wp=WeakPointer<__T__>;
public:
    template<typename __T__,typename ...__A__>
    static SharedPointer<__T__> make_shared(__A__&&..._a_) {
        return SharedPointer<__T__>(
            new __T__(std::forward<__A__>(_a_)...),
            [](__T__*arg) {delete arg; });}
public:
    template<typename __T__>
    using Function=std::function<__T__>;
    template<typename __TF__>
    class SharedPointerFunction:public SharedPointer<const Function<__TF__>> {
    private:
        using _F_=Function<__TF__>;
        using _P_=SharedPointer<const _F_>;
    public:
        SharedPointerFunction(decltype(nullptr)) {}
        SharedPointerFunction()=default;
        SharedPointerFunction(_P_/**/arg):_P_(std::move(arg)) {}
        SharedPointerFunction(_F_/**/arg):_P_(make_shared<_F_>(std::move(arg))) {}
        SharedPointerFunction&operator=(const SharedPointerFunction&)=default;
        SharedPointerFunction&operator=(SharedPointerFunction&&)=default;
        template<typename __U__>
        SharedPointerFunction&operator=(__U__&&_u_) {
            SharedPointerFunction _t_=std::forward<__U__>(_u_);
            return(*this=std::move(_t_));
        }
        operator bool()const { return (this->get())&&bool(*(this->get())); }

        template<typename ...__A__>
        decltype(auto)operator()(__A__&&..._a_) {
            return(*(this->get()))(std::forward<__A__>(_a_)...);
        }

        template<typename ...__A__>
        decltype(auto)operator()(__A__&&..._a_) const {
            return(*(this->get()))(std::forward<__A__>(_a_)...);
        }

    };
    template<typename __T__>
    using spf=SharedPointerFunction<__T__>;
public:
    static void max() {}
    template<typename __T0__>
    constexpr static decltype(auto) max(__T0__&&_v0_) { return std::forward<__T0__>(_v0_); }
    template<typename __T0__>
    constexpr static decltype(auto) max(const __T0__&_v0_,const __T0__&_v1_) {
        return ((_v0_>_v1_)?_v0_:_v1_);
    }
    template<typename __T0__,typename __T1__>
    constexpr static auto max(const __T0__&_v0_,const __T1__&_v1_) {
        using __T__=std::common_type_t<__T0__,__T1__>;
        return std::max<__T__>(_v0_,_v1_);
    }
    template<typename __T0__,typename __T1__,typename ...__A__>
    constexpr static auto max(const __T0__&_v0_,const __T1__&_v1_,const __A__&..._a_) {
        using __T__=std::common_type_t<__T0__,__T1__,__A__...>;
        return ___SSS___TypeTraits::max<__T__,__A__...>(std::max<__T__>(_v0_,_v1_),_a_...);
    }
public:
    static void min() {}
    template<typename __T0__>
    constexpr static decltype(auto) min(__T0__&&_v0_) { return std::forward<__T0__>(_v0_); }
    template<typename __T0__>
    constexpr static decltype(auto) min(const __T0__&_v0_,const __T0__&_v1_) {
        return ((_v0_<_v1_)?_v0_:_v1_);
    }
    template<typename __T0__,typename __T1__>
    constexpr static auto min(const __T0__&_v0_,const __T1__&_v1_) {
        using __T__=std::common_type_t<__T0__,__T1__>;
        return std::min<__T__>(_v0_,_v1_);
    }
    template<typename __T0__,typename __T1__,typename ...__A__>
    constexpr static auto min(const __T0__&_v0_,const __T1__&_v1_,const __A__&..._a_) {
        using __T__=std::common_type_t<__T0__,__T1__,__A__...>;
        return ___SSS___TypeTraits::min<__T__,__A__...>(std::min<__T__>(_v0_,_v1_),_a_...);
    }
public:
    /*add code here*/
protected:
    virtual ~___SSS___TypeTraits()=default;
    ___SSS___TypeTraits(const ___SSS___TypeTraits&)=delete;
    ___SSS___TypeTraits&operator=(const ___SSS___TypeTraits&)=delete;
    ___SSS___TypeTraits(___SSS___TypeTraits&&)=delete;
    ___SSS___TypeTraits&operator=(___SSS___TypeTraits&&)=delete;
};

/*zone_namespace_end*/

#endif"""
    pass

if __name__=="__main__":
    ans=get_type_traits().replace("___SSS___","___SSS___");
    with open("ABC.hpp","w") as fp:
        fp.write(ans);
        fp.write("\r\n");
        pass
    pass

