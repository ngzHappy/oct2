﻿#if !defined(_OPENCV_APPLICATION_CONFIGURATION_FILE )
#define _OPENCV_APPLICATION_CONFIGURATION_FILE

#include "core_utility.hpp"
#include <array>
#include <utility>
#include <cstddef>
#include <cstdint>
#include <memory>

/*
--[[demo--]]
application={
        input_images={
                "images:000001",
                "images:000002",
                "images:000003",
        },
        input_data_1d={
            1,2,3,[[4]],5,
        },
        input_data_2d={
            {"1",2,},
            {[==[3]==],4,},
            {5,[[6]]},
        },
        input_data_3d={
            {1.1,2.2,3.3},
            {3.4,4.5,5.6},
            {5.7,6.8,7.9,},
        }
}
*/
class CORE_UTILITYSHARED_EXPORT OpenCVApplicationConfigurationFile {
MACRO_PROTECTED:
    static std::shared_ptr<lua_State> L_;
    lua_State * L__=nullptr;
    OpenCVApplicationConfigurationFile(lua_State *_L):L__(_L) {}
public:

    typedef double NumberType;
    typedef long long IntegerType;

    OpenCVApplicationConfigurationFile(
        const QByteArray /*argv*/,
        const char * /*buildpath*/,
        const char * /*lua file name like abc.lua*/);
    ~OpenCVApplicationConfigurationFile();
    QStringList getInputImagesNames(const QStringList &/*default*/)const;
    QStringList getInputImagesNames()const { return getInputImagesNames(QStringList{}); }
    QStringList getInputImagesNames(const QString & _default_)const { return getInputImagesNames(QStringList{ _default_ }); }

    template<typename _T_=NumberType,typename _Vector_=std::vector<_T_>>
    _Vector_ getInputData1D()const;
    template<typename _T_=NumberType,typename _Vector_=std::vector<std::pair<_T_,_T_>>>
    _Vector_ getInputData2D()const;
    template<typename _T_=NumberType,typename _Vector_=std::vector<std::array<_T_,3>>>
    _Vector_ getInputData3D()const;

    template<typename _T_=IntegerType,typename _Vector_=std::vector<_T_>>
    _Vector_ getInputData1DInteger()const;
    template<typename _T_=IntegerType,typename _Vector_=std::vector<std::pair<_T_,_T_>>>
    _Vector_ getInputData2DInteger()const;
    template<typename _T_=IntegerType,typename _Vector_=std::vector<std::array<_T_,3>>>
    _Vector_ getInputData3DInteger()const;

MACRO_PROTECTED:
    QByteArray getLocalTextCodecName(const QByteArray &/*default*/)const;
private:
    std::shared_ptr<const void> _p_begin_read_data_1d()const;
    void _p_end_read_data_1d()const;
    bool _p_get_1d_data(NumberType &)const;
    bool _p_get_1d_data(IntegerType &)const;

    std::shared_ptr<const void> _p_begin_read_data_2d()const;
    void _p_end_read_data_2d()const;
    bool _p_get_2d_data(NumberType &,NumberType &)const;
    bool _p_get_2d_data(IntegerType &,IntegerType&)const;

    std::shared_ptr<const void> _p_begin_read_data_3d()const;
    void _p_end_read_data_3d()const;
    bool _p_get_3d_data(NumberType &,NumberType &,NumberType&)const;
    bool _p_get_3d_data(IntegerType &,IntegerType&,IntegerType&)const;
};

template<
    typename _T_,
    typename _Vector_
>
_Vector_ OpenCVApplicationConfigurationFile::getInputData1D()const {
    struct _v_Locker {
    private:
        const OpenCVApplicationConfigurationFile * const _this_;
        std::shared_ptr<const void> _data_;
    public:
        _v_Locker(const OpenCVApplicationConfigurationFile *t):_this_(t) {
            _data_=_this_->_p_begin_read_data_1d();
        }
        ~_v_Locker() {
            _data_.reset();
            _this_->_p_end_read_data_1d();
        }
    };
    try {
        _Vector_ _v_ans;
        _v_Locker _v_locker(this);
        NumberType _v_data;
        while (_p_get_1d_data(_v_data)) {
            _v_ans.push_back(static_cast<_T_>(_v_data));
        }
        return std::move(_v_ans);
    }
    catch (...) {
        return _Vector_{};
    }

}

template<
    typename _T_,
    typename _Vector_
>
_Vector_ OpenCVApplicationConfigurationFile::getInputData2D() const {
    struct _v_Locker {
    private:
        const OpenCVApplicationConfigurationFile * const _this_;
        std::shared_ptr<const void> _data_;
    public:
        _v_Locker(const OpenCVApplicationConfigurationFile *t):_this_(t) {
            _data_=_this_->_p_begin_read_data_2d();
        }
        ~_v_Locker() {
            _data_.reset();
            _this_->_p_end_read_data_2d();
        }
    };
    try {
        _Vector_ _v_ans;
        _v_Locker _v_locker(this);
        NumberType _v_data_1; NumberType _v_data_2;
        while (_p_get_2d_data(_v_data_1,_v_data_2)) {
            _v_ans.push_back(
            { static_cast<_T_>(_v_data_1) ,static_cast<_T_>(_v_data_2) }
            );
        }
        return std::move(_v_ans);
    }
    catch (...) {
        return _Vector_{};
    }

}

template<
    typename _T_,
    typename _Vector_
>
_Vector_ OpenCVApplicationConfigurationFile::getInputData3D()const {
    struct _v_Locker {
    private:
        const OpenCVApplicationConfigurationFile * const _this_;
        std::shared_ptr<const void> _data_;
    public:
        _v_Locker(const OpenCVApplicationConfigurationFile *t):_this_(t) {
            _data_=_this_->_p_begin_read_data_3d();
        }
        ~_v_Locker() {
            _data_.reset();
            _this_->_p_end_read_data_3d();
        }
    };
    try {
        _Vector_ _v_ans;
        _v_Locker _v_locker(this);
        NumberType _v_data_1;
        NumberType _v_data_2;
        NumberType _v_data_3;
        while (_p_get_3d_data(_v_data_1,_v_data_2,_v_data_3)) {
            _v_ans.push_back(
            {
                static_cast<_T_>(_v_data_1),
                static_cast<_T_>(_v_data_2),
                static_cast<_T_>(_v_data_3)
            }
            );
        }
        return std::move(_v_ans);
    }
    catch (...) {
        return _Vector_{};
    }

}

template<
    typename _T_,
    typename _Vector_
>
_Vector_ OpenCVApplicationConfigurationFile::getInputData1DInteger()const {
    struct _v_Locker {
    private:
        const OpenCVApplicationConfigurationFile * const _this_;
        std::shared_ptr<const void> _data_;
    public:
        _v_Locker(const OpenCVApplicationConfigurationFile *t):_this_(t) {
            _data_=_this_->_p_begin_read_data_1d();
        }
        ~_v_Locker() {
            _data_.reset();
            _this_->_p_end_read_data_1d();
        }
    };
    try {
        _Vector_ _v_ans;
        _v_Locker _v_locker(this);
        IntegerType _v_data;
        while (_p_get_1d_data(_v_data)) {
            _v_ans.push_back(static_cast<_T_>(_v_data));
        }
        return std::move(_v_ans);
    }
    catch (...) {
        return _Vector_{};
    }

}

template<
    typename _T_,
    typename _Vector_
>
_Vector_ OpenCVApplicationConfigurationFile::getInputData2DInteger()const {
    struct _v_Locker {
    private:
        const OpenCVApplicationConfigurationFile * const _this_;
        std::shared_ptr<const void> _data_;
    public:
        _v_Locker(const OpenCVApplicationConfigurationFile *t):_this_(t) {
            _data_=_this_->_p_begin_read_data_2d();
        }
        ~_v_Locker() {
            _data_.reset();
            _this_->_p_end_read_data_2d();
        }
    };
    try {
        _Vector_ _v_ans;
        _v_Locker _v_locker(this);
        IntegerType _v_data_1; IntegerType _v_data_2;
        while (_p_get_2d_data(_v_data_1,_v_data_2)) {
            _v_ans.push_back(
            { static_cast<_T_>(_v_data_1) ,static_cast<_T_>(_v_data_2) }
            );
        }
        return std::move(_v_ans);
    }
    catch (...) {
        return _Vector_{};
    }

}

template<
    typename _T_,
    typename _Vector_
>
_Vector_ OpenCVApplicationConfigurationFile::getInputData3DInteger()const {
    struct _v_Locker {
    private:
        const OpenCVApplicationConfigurationFile * const _this_;
        std::shared_ptr<const void>_data_;
    public:
        _v_Locker(const OpenCVApplicationConfigurationFile *t):_this_(t) {
            _data_=_this_->_p_begin_read_data_3d();
        }
        ~_v_Locker() {
            _data_.reset();
            _this_->_p_end_read_data_3d();
        }
    };
    try {
        _Vector_ _v_ans;
        _v_Locker _v_locker(this);
        IntegerType _v_data_1;
        IntegerType _v_data_2;
        IntegerType _v_data_3;
        while (_p_get_3d_data(_v_data_1,_v_data_2,_v_data_3)) {
            _v_ans.push_back(
            {
                static_cast<_T_>(_v_data_1),
                static_cast<_T_>(_v_data_2),
                static_cast<_T_>(_v_data_3)
            }
            );
        }
        return std::move(_v_ans);
    }
    catch (...) {
        return _Vector_{};
    }

}

#endif



