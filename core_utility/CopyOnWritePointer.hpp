#if !defined(__COPY__ON__WRITE__POINTER_0x00_)
#define __COPY__ON__WRITE__POINTER_0x00_

#include <memory>
#include <utility>
#include <type_traits>

template<typename _T_>
class CopyOnWritePointer {
public:
    typedef typename std::shared_ptr<_T_>::element_type element_type;
    typedef std::add_const_t<element_type> const_element_type;
private:
    template<typename _U_>friend class CopyOnWritePointer;
    std::shared_ptr<_T_> copy_on_write_data_;
    template<typename _U_,bool _is_read_only_>
    class Get {
    public:
        static element_type * get(CopyOnWritePointer * _this_) {
            return _this_->copy_on_write_data_.get();
        }
    };
    template<typename _U_>
    class Get<_U_,false> {
    public:
        static element_type *get(CopyOnWritePointer * _this_) {
            if (_this_->copy_on_write_data_.use_count()>1) {
                auto _tmp_=std::shared_ptr<_T_>(new _T_(*(_this_->copy_on_write_data_)));
                _this_->copy_on_write_data_=_tmp_;
            }
            return _this_->copy_on_write_data_.get();
        }
    };
public:

    CopyOnWritePointer()=default;
    CopyOnWritePointer(decltype(nullptr)) {}
    CopyOnWritePointer(const CopyOnWritePointer&)=default;
    CopyOnWritePointer(CopyOnWritePointer&&)=default;
    template<typename _U_>
    CopyOnWritePointer(const std::shared_ptr<_U_>&_v_):copy_on_write_data_(_v_) {}
    template<typename _U_>
    CopyOnWritePointer(std::shared_ptr<_U_>&&_v_):copy_on_write_data_(std::move(_v_)) {}
    template<typename _U_>
    CopyOnWritePointer(const CopyOnWritePointer<_U_>&_v_):copy_on_write_data_(_v_.copy_on_write_data_) {}
    template<typename _U_>
    CopyOnWritePointer(CopyOnWritePointer<_U_>&&_v_):copy_on_write_data_(std::move(_v_.copy_on_write_data_)) {}
    template<typename ... _U_>
    CopyOnWritePointer(std::unique_ptr<_U_...>&& _v_):copy_on_write_data_(std::move(_v_)) {}
    template<typename ..._U_>
    CopyOnWritePointer(std::weak_ptr<_U_...>&&_v_):copy_on_write_data_(std::move(_v_)) {}
    template<typename ..._U_>
    CopyOnWritePointer(const std::weak_ptr<_U_...>&_v_):copy_on_write_data_(_v_) {}
    template<typename _U_>
    CopyOnWritePointer(_U_*_v_):copy_on_write_data_(_v_) {}
    template<typename _0_,typename _1_,typename ... _U_>
    CopyOnWritePointer(_0_&& _v0_,_1_&& _v1_,_U_&&..._v_):
        copy_on_write_data_(std::forward<_0_>(_v0_),std::forward<_1_>(_v1_),std::forward<_U_>(_v_)...) {}
    CopyOnWritePointer&operator=(const CopyOnWritePointer&)=default;
    CopyOnWritePointer&operator=(CopyOnWritePointer&&)=default;
    ~CopyOnWritePointer()=default;

    const_element_type& operator*() const { return *copy_on_write_data_; }
    const_element_type* operator->()const { return copy_on_write_data_.get(); }
    const_element_type* get() const { return copy_on_write_data_.get(); }

    element_type& operator*() { return *(Get<void,std::is_const<_T_>::value>::get(this)); }
    element_type* operator->() { return Get<void,std::is_const<_T_>::value>::get(this); }
    element_type* get() { return Get<void,std::is_const<_T_>::value>::get(this); }

    std::shared_ptr<element_type> getSharedPointer()const { return copy_on_write_data_; }
    auto use_count() const { return copy_on_write_data_.use_count(); }
};

#endif

