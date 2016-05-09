

def get_type_traits():
    return"""/*type traits*/
#ifndef __PRAGMA_ONCE____SSS___HXX_0x00
#define __PRAGMA_ONCE____SSS___HXX_0x00

#include <memory>
#include <cstdlib>
#include <utility>
#include <cstddef>
#include <cstdint>
#include <iterator>
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

