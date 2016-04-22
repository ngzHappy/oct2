#if !defined(_OPENCV_APPLICATION_CONFIGURATION_FILE )
#define _OPENCV_APPLICATION_CONFIGURATION_FILE

#include "core_utility.hpp"
#include <list>
#include <array>
#include <utility>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <iterator>

class _STATIC_OpenCVApplicationConfigurationFile {
public:
    static std::shared_ptr<lua_State> L_;
};
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
        },
        input_gif_data{
            width=100,
            height=100,
            {"images:000001",100--[[time--]]},
            {"images:000002",100--[[time--]]},
            {"images:000003",100--[[time--]]},
        },
}
*/
class CORE_UTILITYSHARED_EXPORT OpenCVApplicationConfigurationFile {
MACRO_PROTECTED:
    lua_State * L__=nullptr;
    OpenCVApplicationConfigurationFile(lua_State *_L):L__(_L) {}
    std::shared_ptr<const void> _m_manager;
public:

    class GifMakerData {
    public:
        struct Item {
            QString fileName;
            std::int32_t time;
            Item(std::int32_t t,const QString & f):fileName(f),time(t) {}
            Item(const QString & f,std::int32_t t):fileName(f),time(t) {}
        };
        std::int32_t width=-1;
        std::int32_t height=-1;
        std::shared_ptr<const std::list<Item>>data;
        operator bool()const { 
            if (height<=0) { return false; }
            if (width<=0) { return false; }
            return (bool(data)&&data->empty()==false);
        }
    };

    typedef double NumberType;
    typedef long long IntegerType;

    OpenCVApplicationConfigurationFile(
        QByteArray /*local8byte: full exe name lick c:/abc/xxx.exe */,
        QByteArray /*local8byte: append search path */,
        QByteArray /*local8byte: lua file name like abc.lua or abc.zip */);
    OpenCVApplicationConfigurationFile(
        std::shared_ptr<lua_State>,
        QByteArray,
        QByteArray,
        QByteArray);
    ~OpenCVApplicationConfigurationFile();
    QStringList getInputImagesNames(const QStringList &/*default*/)const;
    QStringList getInputImagesNames()const { return getInputImagesNames(QStringList{}); }
    QStringList getInputImagesNames(const QString & _default_)const { return getInputImagesNames(QStringList{ _default_ }); }
    GifMakerData getInputGifMaderData()const;

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

    template<typename _T_=NumberType,typename _Push_Back_Iterator_ >
    void getInputData1D(_Push_Back_Iterator_)const;
    template<typename _T_=NumberType,typename _Push_Back_Iterator_ >
    void getInputData2D(_Push_Back_Iterator_)const;
    template<typename _T_=NumberType,typename _Push_Back_Iterator_ >
    void getInputData3D(_Push_Back_Iterator_)const;

    template<typename _T_=IntegerType,typename _Push_Back_Iterator_ >
    void getInputData1DInteger(_Push_Back_Iterator_)const;
    template<typename _T_=IntegerType,typename _Push_Back_Iterator_ >
    void getInputData2DInteger(_Push_Back_Iterator_)const;
    template<typename _T_=IntegerType,typename _Push_Back_Iterator_ >
    void getInputData3DInteger(_Push_Back_Iterator_)const;

MACRO_PROTECTED:
    QByteArray getLocalTextCodecName(const QByteArray &/*default*/)const;
private:
    std::shared_ptr<const void> _p_begin_read_data_1d()const;
    bool _p_get_1d_data(NumberType &)const;
    bool _p_get_1d_data(IntegerType &)const;

    std::shared_ptr<const void> _p_begin_read_data_2d()const;
    bool _p_get_2d_data(NumberType &,NumberType &)const;
    bool _p_get_2d_data(IntegerType &,IntegerType&)const;

    std::shared_ptr<const void> _p_begin_read_data_3d()const;
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
        }
    };
    try {
        _Vector_ _v_ans;
        _v_Locker _v_locker(this);
        NumberType _v_data;
        while (_p_get_1d_data(_v_data)) {
            _v_ans.push_back({ static_cast<_T_>(_v_data) });
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
        }
    };
    try {
        _Vector_ _v_ans;
        _v_Locker _v_locker(this);
        IntegerType _v_data;
        while (_p_get_1d_data(_v_data)) {
            _v_ans.push_back({ static_cast<_T_>(_v_data) });
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

template<
    typename _T_,
    typename _Vector_
>
void OpenCVApplicationConfigurationFile::getInputData1D(_Vector_ _v_ans)const {
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
        }
    };
    try {
        _v_Locker _v_locker(this);
        NumberType _v_data;
        while (_p_get_1d_data(_v_data)) {
            *_v_ans={ static_cast<_T_>(_v_data) };
            ++_v_ans;
        }
        return;
    }
    catch (...) {
        return;
    }

}

template<
    typename _T_,
    typename _Vector_
>
void OpenCVApplicationConfigurationFile::getInputData2D(_Vector_ _v_ans) const {
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
        }
    };
    try {
        _v_Locker _v_locker(this);
        NumberType _v_data_1; NumberType _v_data_2;
        while (_p_get_2d_data(_v_data_1,_v_data_2)) {
            *_v_ans={ static_cast<_T_>(_v_data_1) ,static_cast<_T_>(_v_data_2) };
            ++_v_ans;
        }
        return;
    }
    catch (...) {
        return;
    }

}

template<
    typename _T_,
    typename _Vector_
>
void OpenCVApplicationConfigurationFile::getInputData3D(_Vector_ _v_ans)const {
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
        }
    };
    try {
        _v_Locker _v_locker(this);
        NumberType _v_data_1;
        NumberType _v_data_2;
        NumberType _v_data_3;
        while (_p_get_3d_data(_v_data_1,_v_data_2,_v_data_3)) {
            *_v_ans=
            {
                static_cast<_T_>(_v_data_1),
                static_cast<_T_>(_v_data_2),
                static_cast<_T_>(_v_data_3)
            }; ++_v_ans;
        }
        return;
    }
    catch (...) {
        return;
    }

}

template<
    typename _T_,
    typename _Vector_
>
void OpenCVApplicationConfigurationFile::getInputData1DInteger(_Vector_ _v_ans)const {
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
        }
    };
    try {
        _v_Locker _v_locker(this);
        IntegerType _v_data;
        while (_p_get_1d_data(_v_data)) {
            *_v_ans={ static_cast<_T_>(_v_data) };
            ++_v_ans;
        }
        return;
    }
    catch (...) {
        return;
    }

}

template<
    typename _T_,
    typename _Vector_
>
void OpenCVApplicationConfigurationFile::getInputData2DInteger(_Vector_ _v_ans)const {
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
        }
    };
    try {
        _v_Locker _v_locker(this);
        IntegerType _v_data_1; IntegerType _v_data_2;
        while (_p_get_2d_data(_v_data_1,_v_data_2)) {
            *_v_ans=
            { static_cast<_T_>(_v_data_1) ,static_cast<_T_>(_v_data_2) };
            ++_v_ans;
        }
        return;
    }
    catch (...) {
        return;
    }

}

template<
    typename _T_,
    typename _Vector_
>
void OpenCVApplicationConfigurationFile::getInputData3DInteger(_Vector_ _v_ans)const {
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
        }
    };
    try {
        _v_Locker _v_locker(this);
        IntegerType _v_data_1;
        IntegerType _v_data_2;
        IntegerType _v_data_3;
        while (_p_get_3d_data(_v_data_1,_v_data_2,_v_data_3)) {
            *_v_ans=
            {
                static_cast<_T_>(_v_data_1),
                static_cast<_T_>(_v_data_2),
                static_cast<_T_>(_v_data_3)
            }; ++_v_ans;
        }
        return;
    }
    catch (...) {
        return;
    }

}


#endif



