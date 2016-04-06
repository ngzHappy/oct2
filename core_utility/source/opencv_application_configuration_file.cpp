#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#define LUA_LIB

#include "../opencv_application_configuration_file.hpp"
#include <iostream>
#include <fstream>
#include <string>

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

void init(
    OpenCVApplicationConfigurationFile * _a_this,
    int _a_argc,char ** _a_argv,
    const char * _a_build_path,
    const char * _a_lua_file_name) {
    std::string _v_build_path;
    if (_a_build_path) { _v_build_path=_a_build_path; }
    if ((_a_argc>=1)&&(_a_argv)) {
        std::string application_path(_a_argv[0]);
        if (application_path.empty()) { return; }
        {
            const auto last_=application_path.find_last_of("/\\");
            if (last_==std::string::npos) { return; }
            application_path=std::string(
                application_path.begin(),
                application_path.begin()+last_);
            if (application_path.empty()) { return; }
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
        _a_this->L_=LuaUtility::createLuaState();
        LUAStateLock __lock(_a_this->L_.get());
        lua_pushcfunction(_a_this->L_.get(),&__private::error_function_lua_loadfile);
        const auto error_fun_pos_=lua_gettop(_a_this->L_.get());
        luaL_loadfile(_a_this->L_.get(),file_name_.c_str());
        lua_pcall(_a_this->L_.get(),0,LUA_MULTRET,error_fun_pos_);
        _a_this->L__=_a_this->L_.get();
        std::cout.flush();
    }
}
}
}

const OpenCVApplicationConfigurationFile & CoreUtility::getConfigurationFile() {
    static OpenCVApplicationConfigurationFile ans_(
                OpenCVApplicationConfigurationFile::L_.get()
                ) ;
    if(ans_.L__){return ans_;}
    ans_.L__=OpenCVApplicationConfigurationFile::L_.get();
    return ans_;
}

QStringList OpenCVApplicationConfigurationFile::getInputImagesNames(const QStringList & _a_default)const {
    if (L__==nullptr) { return _a_default; }
    __private::LUAStateLock _L(L__);

    luaL_dostring(L__,"return application.input_images");
    if (lua_isstring(L__,-1)) {
        QString ans_(QString::fromUtf8(lua_tostring(L__,-1)));
        if (ans_.isEmpty()) {return _a_default;}
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

        if (ans_.isEmpty()) {return _a_default;}
        return std::move(ans_);
    }

    return _a_default;
}

QByteArray OpenCVApplicationConfigurationFile::getLocalTextCodecName(const QByteArray & _a_default )const {
    if (L__==nullptr) { return _a_default; }
    __private::LUAStateLock _L(L__);
    luaL_dostring(L__,"return application.text_codec");
    if(lua_isstring(L__,-1)){
        QByteArray ans_(lua_tostring(L__,-1));
        if (ans_.isEmpty()) {return _a_default;}
        return std::move(ans_);
    }
    return _a_default;
}

OpenCVApplicationConfigurationFile::OpenCVApplicationConfigurationFile(
    int _a_argc,
    char ** _a_argv,
    const char * _a_build_path,
    const char * _a_lua_file_name) {
    if (L_) { L__=L_.get(); }
    else {
        __private::init(this,_a_argc,_a_argv,_a_build_path,_a_lua_file_name);
    }
}

OpenCVApplicationConfigurationFile::~OpenCVApplicationConfigurationFile(){
}
