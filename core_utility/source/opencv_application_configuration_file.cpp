#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#define LUA_LIB

#include "../opencv_application_configuration_file.hpp"
#include "../lua/lua.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <QtCore/qdebug.h>
#include "../core_utility.hpp"

/*静态数据*/
std::shared_ptr<lua_State> OpenCVApplicationConfigurationFile::L_;

namespace {
namespace __private {
int error_function_lua_loadfile(lua_State * L) {
    size_t n=0;
    const char * value_=luaL_tolstring(L,-1,&n);
    if (value_ && n) {
        qDebug().noquote()<<"lua load file error:"<<value_;
    }
    return 0;
}
}
}

namespace {
namespace __private {

class LUAStateLock {
    int top_;
    lua_State * L;
    LUAStateLock()=delete;
    LUAStateLock(const LUAStateLock &)=delete;
    LUAStateLock&operator=(const LUAStateLock &)=delete;
    LUAStateLock(LUAStateLock &&)=delete;
    LUAStateLock&operator=(LUAStateLock &&)=delete;
public:
    LUAStateLock(lua_State * _L):L(_L) {
        top_=lua_gettop(L);
    }
    ~LUAStateLock() { lua_settop(L,top_); }
};

char to_lower_(char i) {
    if ((i>='A')&&(i<='Z')) { return char(i-'A'+'a'); }
    return i;
}

void init(
    OpenCVApplicationConfigurationFile * _a_this,
    int _a_argc,char ** _a_argv,
    const char * _a_build_path,
    const char * _a_lua_file_name) {
    std::string _v_build_path;
    if (_a_build_path) { _v_build_path=_a_build_path; }
    if ((_a_argc>=1)&&(_a_argv)) {
        std::string application_path(_a_argv[0]);
        if (application_path.empty()) { std::cout<<"app empty"<<std::endl; return; }
        {
            const auto last_=application_path.find_last_of("/\\");
            if (last_==std::string::npos) {
                std::cout<<"application path :"<<application_path
                    <<" can not find / \\ "<<std::endl; return;
            }
            application_path=std::string(
                application_path.begin(),
                application_path.begin()+last_);
            if (application_path.empty()) { std::cout<<"app empty ??"<<std::endl; return; }
        }
        std::string file_name_=_a_lua_file_name;
        {
            std::ifstream ifs(file_name_,std::ios::in);
            if (false==ifs.is_open()) {
                file_name_=application_path+"/"+_a_lua_file_name;
                ifs.open(file_name_,std::ios::in);
                if (ifs.is_open()==false) {
                    if (_v_build_path.empty()) { return; }
                    file_name_=_v_build_path+"/"+_a_lua_file_name;
                    ifs.open(file_name_,std::ios::in);
                    if (ifs.is_open()==false) {
                        file_name_=_v_build_path+_a_lua_file_name;
                        ifs.open(file_name_,std::ios::in);
                        if (ifs.is_open()==false) { return; }
                    }
                }
            }
        }

        std::cout<<"lua configure filename: "<<file_name_<<std::endl;

        std::string lua_this_file_name_=_a_lua_file_name;
        if (
            (lua_this_file_name_.size()<4)||
            !(
            (to_lower_(*(lua_this_file_name_.rbegin()))=='p')&&
            (to_lower_(*(lua_this_file_name_.rbegin()+1))=='i')&&
            (to_lower_(*(lua_this_file_name_.rbegin()+2))=='z')&&
            ((*(lua_this_file_name_.rbegin()+3))=='.')
            )
            ) {
            _a_this->L_=LuaUtility::createLuaState();
            LUAStateLock __lock(_a_this->L_.get())/*锁定lua栈区*/;
            lua_pushcfunction(_a_this->L_.get(),&__private::error_function_lua_loadfile);
            const auto error_fun_pos_=lua_gettop(_a_this->L_.get());
            if ( LuaUtility::loadFile(
                _a_this->L_.get(),
                QString::fromLocal8Bit(file_name_.c_str(),
                static_cast<int>(file_name_.size())),
                QString::fromLocal8Bit(lua_this_file_name_.c_str(),
                static_cast<int>(lua_this_file_name_.size()))
                )/*从plain文件中读取文件*/) {
                lua_pcall(_a_this->L_.get(),0,LUA_MULTRET,error_fun_pos_);
            }
            _a_this->L__=_a_this->L_.get();
        }
        else /*zip file*/
        {
            lua_this_file_name_.resize(lua_this_file_name_.size()-4);
            lua_this_file_name_+=".lua";

            _a_this->L_=LuaUtility::createLuaState();
            LUAStateLock __lock(_a_this->L_.get())/*锁定lua栈区*/;
            lua_pushcfunction(_a_this->L_.get(),&__private::error_function_lua_loadfile);
            const auto error_fun_pos_=lua_gettop(_a_this->L_.get());
            if (
                LuaUtility::loadFile(
                _a_this->L_.get(),
                QString::fromLocal8Bit(file_name_.c_str(),
                static_cast<int>(file_name_.size())),
                QString::fromLocal8Bit(lua_this_file_name_.c_str(),
                static_cast<int>(lua_this_file_name_.size()))
                )/*从zip文件中读取文件*/
                ) {
                /*执行文件*/
                lua_pcall(_a_this->L_.get(),0,LUA_MULTRET,error_fun_pos_);
            }
            _a_this->L__=_a_this->L_.get();
        }

        std::cout.flush();
    }
}
}
}

const OpenCVApplicationConfigurationFile & CoreUtility::getConfigurationFile() {
    static OpenCVApplicationConfigurationFile ans_(
                OpenCVApplicationConfigurationFile::L_.get()
                );
    if (ans_.L__) { return ans_; }
    ans_.L__=OpenCVApplicationConfigurationFile::L_.get();
    return ans_;
}

std::shared_ptr<const void> OpenCVApplicationConfigurationFile::_p_begin_read_data_1d()const {
    if (L__==nullptr) { throw nullptr; }
    std::shared_ptr<const void> ans_(new __private::LUAStateLock(L__));
    luaL_dostring(L__,"return application.input_data_1d");
    if (false==lua_istable(L__,-1)) { throw nullptr; }
    lua_pushnil(L__);
    return std::move(ans_);
}

void OpenCVApplicationConfigurationFile::_p_end_read_data_1d()const {

}

bool OpenCVApplicationConfigurationFile::_p_get_1d_data(
    NumberType & __1)const {
    if (lua_next(L__,-2/*table index*/)) {
        int is_num_=0;
        __1=lua_tonumberx(L__,-1,&is_num_);
        if (false==is_num_) {
            return false;
        }
        lua_pop(L__,1);
        return true;
    }
    return false;
}

bool OpenCVApplicationConfigurationFile::_p_get_1d_data(
    IntegerType &__1)const {
    if (lua_next(L__,-2/*table index*/)) {
        int is_num_=0;
        __1=lua_tointegerx(L__,-1,&is_num_);
        if (false==is_num_) {
            const auto ___1=(lua_tonumberx(L__,-1,&is_num_));
            if (false==is_num_) { return false; }
            /*?????*/
            __1=static_cast<IntegerType>(___1);
        }
        lua_pop(L__,1);
        return true;
    }
    return false;
}

std::shared_ptr<const void> OpenCVApplicationConfigurationFile::_p_begin_read_data_2d()const {
    if (L__==nullptr) { throw nullptr; }
    std::shared_ptr<const void> ans_(new __private::LUAStateLock(L__));
    luaL_dostring(L__,"return application.input_data_2d");
    if (false==lua_istable(L__,-1)) { throw nullptr; }
    lua_pushnil(L__);
    return std::move(ans_);
}

void OpenCVApplicationConfigurationFile::_p_end_read_data_2d() const {

}

bool OpenCVApplicationConfigurationFile::_p_get_2d_data(
    NumberType &__1,
    NumberType &__2)const {
    if (lua_next(L__,-2/*table index*/)) {
        if (lua_istable(L__,-1)) {
            auto table_index=lua_gettop(L__);
            lua_pushnil(L__);
            if (_p_get_1d_data(__1)) {
                if (_p_get_1d_data(__2)) {
                    lua_settop(L__,table_index-1)/*pop the table*/;
                    return true;
                }
            }
        }
    }
    return false;
}

bool OpenCVApplicationConfigurationFile::_p_get_2d_data(
    IntegerType &__1,
    IntegerType &__2)const {
    if (lua_next(L__,-2/*table index*/)) {
        if (lua_istable(L__,-1)) {
            auto table_index=lua_gettop(L__);
            lua_pushnil(L__);
            if (_p_get_1d_data(__1)) {
                if (_p_get_1d_data(__2)) {
                    lua_settop(L__,table_index-1)/*pop the table*/;
                    return true;
                }
            }
        }
    }
    return false;
}

std::shared_ptr<const void> OpenCVApplicationConfigurationFile::_p_begin_read_data_3d()const {
    if (L__==nullptr) { throw nullptr; }
    std::shared_ptr<const void> ans_(new __private::LUAStateLock(L__));
    luaL_dostring(L__,"return application.input_data_3d");
    if (false==lua_istable(L__,-1)) { throw nullptr; }
    lua_pushnil(L__);
    return std::move(ans_);
}

void OpenCVApplicationConfigurationFile::_p_end_read_data_3d()const {

}

bool OpenCVApplicationConfigurationFile::_p_get_3d_data(
    NumberType &__1,
    NumberType &__2,
    NumberType &__3)const {
    if (lua_next(L__,-2/*table index*/)) {
        if (lua_istable(L__,-1)) {
            const auto table_index=lua_gettop(L__);
            lua_pushnil(L__);
            if (_p_get_1d_data(__1)) {
                if (_p_get_1d_data(__2)) {
                    if (_p_get_1d_data(__3)) {
                        lua_settop(L__,table_index-1)/*pop the table*/;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool OpenCVApplicationConfigurationFile::_p_get_3d_data(
    IntegerType &__1,
    IntegerType &__2,
    IntegerType &__3)const {
    if (lua_next(L__,-2/*table index*/)) {
        if (lua_istable(L__,-1)) {
            const auto table_index=lua_gettop(L__);
            lua_pushnil(L__);
            if (_p_get_1d_data(__1)) {
                if (_p_get_1d_data(__2)) {
                    if (_p_get_1d_data(__3)) {
                        lua_settop(L__,table_index-1)/*pop the table*/;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

QStringList OpenCVApplicationConfigurationFile::getInputImagesNames(const QStringList & _a_default)const {
    if (L__==nullptr) { return _a_default; }
    __private::LUAStateLock _L(L__);

    luaL_dostring(L__,"return application.input_images");
    if (lua_isstring(L__,-1)) {
        QString ans_(QString::fromUtf8(lua_tostring(L__,-1)));
        if (ans_.isEmpty()) { return _a_default; }
        return  QStringList{ ans_ };
    }

    if (lua_istable(L__,-1)) {
        QStringList ans_;

        lua_pushnil(L__);

        while (lua_next(L__,-2)) {
            QString ans__(QString::fromUtf8(lua_tostring(L__,-1)));
            if (ans__.isEmpty()==false) { ans_.push_back(std::move(ans__)); }
            lua_pop(L__,1);
        }

        if (ans_.isEmpty()) { return _a_default; }
        return std::move(ans_);
    }

    return _a_default;
}

QByteArray OpenCVApplicationConfigurationFile::getLocalTextCodecName(const QByteArray & _a_default)const {
    if (L__==nullptr) { return _a_default; }
    __private::LUAStateLock _L(L__);
    luaL_dostring(L__,"return application.text_codec");
    if (lua_isstring(L__,-1)) {
        QByteArray ans_(lua_tostring(L__,-1));
        if (ans_.isEmpty()) { return _a_default; }
        return std::move(ans_);
    }
    return _a_default;
}

OpenCVApplicationConfigurationFile::OpenCVApplicationConfigurationFile(
    const QByteArray _a_arg,
    const char * _a_build_path,
    const char * _a_lua_file_name) {
    if (L_) { L__=L_.get(); }
    else {
        char * _a_argv[]{ const_cast<char *>(_a_arg.constData()) };
        __private::init(this,1,_a_argv,_a_build_path,_a_lua_file_name);
    }
}

OpenCVApplicationConfigurationFile::~OpenCVApplicationConfigurationFile() {
}
