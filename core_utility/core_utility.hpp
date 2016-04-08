#ifndef CORE_UTILITY_HPP
#define CORE_UTILITY_HPP

/***********************************/
//protect public 切换宏
/***********************************/
#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>
#include "core_utility_global.hpp"
#include "ReadOnly.hpp"
#include "getxy.hpp"
struct lua_State;

/*
utility.copyTable
utility.showTable
utility.tableToString
*/
class CORE_UTILITYSHARED_EXPORT LuaUtility {
public:
    /*create lua state*/
    static std::shared_ptr<lua_State> createLuaState();
    static std::shared_ptr<lua_State> createLuaState(lua_State*);
    /*
    load file
    support .zip ans plain file
    */
    static int loadFile(lua_State * const L,const QString& __file_name,const QString & __zip_file_name=QString());
    static int loadFile(lua_State * const L,QString&&__file_name,QString &&__zip_file_name=QString());
    static int loadFile(lua_State * const L,QString&& __file_name,const QString & __zip_file_name=QString());
    static int loadFile(lua_State * const L,const QString&__file_name,QString &&__zip_file_name=QString());
    /*init utility lib*/
    static int openLib(lua_State * L);
    /*load utility module*/
    static void loadModule(lua_State * L);
    /*input a table out put a table*/
    static int copyTable(lua_State * L);
    /*input table name and table*/
    static int showTable(lua_State * L);
    /*input table name and table*/
    static int tableToString(lua_State * L);
MACRO_PROTECTED:
    /*input table name and table*/
    static void printTable(lua_State * L,std::function<void(const std::string &)> print_);
private:
    template<typename _T_,typename _U_>
    static int _p_loadFile(lua_State * L,_T_&&,_U_&&);
};

class OpenCVApplicationConfigurationFile;
class CORE_UTILITYSHARED_EXPORT CoreUtility : public LuaUtility {
public:
    CoreUtility();
    ~CoreUtility();

    static const OpenCVApplicationConfigurationFile & getConfigurationFile();
};

inline QString operator""_qs(const char * utf8data__,std::size_t l__) {
    return QString::fromUtf8(utf8data__,l__);
}

#endif // CORE_UTILITY_HPP


