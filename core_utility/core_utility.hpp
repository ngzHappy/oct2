#ifndef CORE_UTILITY_HPP
#define CORE_UTILITY_HPP

/***********************************/
//protect public 切换宏
/***********************************/
#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include "core_utility_global.hpp"
#include "quazip/quazip.h"
#include "quazip/quazipdir.h"
#include "quazip/quazipfile.h"
#include "quazip/quazipfileinfo.h"
#include "quazip/GZipCompressor.hpp"
#include "lua/lua.hpp"
#include "ReadOnly.hpp"
#include "getxy.hpp"
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>

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
};

class OpenCVApplicationConfigurationFile;
class CORE_UTILITYSHARED_EXPORT CoreUtility : public LuaUtility
{
public:
    CoreUtility();
    ~CoreUtility();

    static const OpenCVApplicationConfigurationFile & getConfigurationFile() ;
};

inline QString operator""_qs(const char * utf8data__,std::size_t l__) {
    return QString::fromUtf8(utf8data__,l__);
}

#endif // CORE_UTILITY_HPP
