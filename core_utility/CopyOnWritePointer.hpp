﻿#if !defined(__COPY__ON__WRITE__POINTER_0x00_)
#define __COPY__ON__WRITE__POINTER_0x00_

#include <memory>
#include <cassert>
#include <utility>
#include <type_traits>

template<typename _T_>
class CopyOnWritePointer {
public:
    typedef typename std::shared_ptr<_T_>::element_type element_type;
    typedef std::add_const_t<element_type> const_element_type;
    /*
    !!!you must write the function lick
    template<>
    std::shared_ptr<int> CopyOnWritePointer<int>::clone(const std::shared_ptr<int> d) {
    return std::shared_ptr<int>(new int(*d));
    }
    */
    static std::shared_ptr<_T_> clone(const std::shared_ptr<_T_>);
private:
    template<typename _U_>friend class CopyOnWritePointer;
    std::shared_ptr<_T_> copy_on_write_data_;
    template<typename _U_,bool _is_read_only_>
    class Copy {
    public:
        static element_type * get(CopyOnWritePointer * _this_) {
            return _this_->copy_on_write_data_.get();
        }
    };
    template<typename _U_>
    class Copy<_U_,false> {
    public:
        static element_type *get(CopyOnWritePointer * _this_) {
            if (_this_->copy_on_write_data_.use_count()>1) {
                auto _tmp_=clone(_this_->copy_on_write_data_);
                assert(_tmp_.get()!=_this_->copy_on_write_data_.get());
                _this_->copy_on_write_data_=std::move(_tmp_);
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

    element_type& operator*() { return *(Copy<_T_,std::is_const<_T_>::value>::get(this)); }
    element_type* operator->() { return Copy<_T_,std::is_const<_T_>::value>::get(this); }
    element_type* get() { return Copy<_T_,std::is_const<_T_>::value>::get(this); }

    std::shared_ptr<element_type> getSharedPointer() {
        std::shared_ptr<element_type> _ans_;
        if (std::is_const<_T_>::value==false) { _ans_=clone(copy_on_write_data_); }
        else { _ans_=copy_on_write_data_; }
        return std::move(_ans_);
    }
    std::shared_ptr<const_element_type> getSharedPointer()const { return copy_on_write_data_; }
    auto use_count() const { return copy_on_write_data_.use_count(); }
};

#endif

