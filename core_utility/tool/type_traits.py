

def get_type_traits():
    return"""/*type traits*/
class ___SSS___TypeTraits {
public:
    template<typename...>using void_t=void;
    using Size=std::size_t;
    using Integer=std::int32_t;
    template<typename __T__>
    using SharedPointer=std::shared_ptr<__T__>;
    ___SSS___TypeTraits()=default;
    template<typename __T__,typename ...__A__>
    static SharedPointer<__T__> make_shared(__A__&&..._a_) {
        return SharedPointer<__T__>(
            new __T__(std::forward<__A__>(_a_)...),
            [](__T__*arg) {delete arg; });}
protected:
    virtual ~___SSS___TypeTraits()=default;
    ___SSS___TypeTraits(const ___SSS___TypeTraits&)=delete;
    ___SSS___TypeTraits&operator=(const ___SSS___TypeTraits&)=delete;
    ___SSS___TypeTraits(___SSS___TypeTraits&&)=delete;
    ___SSS___TypeTraits&operator=(___SSS___TypeTraits&&)=delete;
};"""
    pass

if __name__=="__main__":
    ans=get_type_traits().replace("___SSS___","ABC");
    with open("ABC.hpp","w") as fp:
        fp.write(ans);
        fp.write("\r\n");
        pass
    pass

