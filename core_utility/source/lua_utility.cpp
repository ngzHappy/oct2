#define LUA_LIB
#include "../core_utility.hpp"
#include "../lua/lua.hpp"
#include "../lua/lstate.h"
#include <QtCore/qdebug.h>

#include "../quazip/quazip.h"
#include "../quazip/quazipfileinfo.h"
#include "../quazip/quazipfile.h"

#include <sstream>
#include <iostream>
#include <cassert>

#if !defined(FLOAT_PRECISION)
namespace {
enum { FLOAT_PRECISION_=16 };
}
#else
namespace {
enum { FLOAT_PRECISION_=FLOAT_PRECISION };
}
#endif

namespace {
namespace __cct {
namespace __private {

std::shared_ptr<lua_State> createLuaState() {
    lua_State * L=luaL_newstate();
    *(L->cpp_user_data_->userCount)=1;

    /*open all library*/
    luaL_openlibs(L);
    LuaUtility::loadModule(L);

    return std::shared_ptr<lua_State>(L,[
        userCount=L->cpp_user_data_->userCount
    ](lua_State * L_) {
        if (L_==nullptr) { return; }
        auto __lock__data__=L_->cpp_user_data_->mutex();
        std::unique_lock<std::recursive_mutex>  _lock_(*(__lock__data__));
        --(*userCount);
        if (*userCount==0) { 
            lua_close(L_); 
            *userCount=-99999;
        }
    });
}

std::shared_ptr<lua_State> createLuaState(lua_State * L) {
    if (L==nullptr) { return nullptr; }
    auto __lock__data__=L->cpp_user_data_->mutex();
    std::unique_lock<std::recursive_mutex>  _lock_(*(__lock__data__));
    ++(*(L->cpp_user_data_->userCount));
    return std::shared_ptr<lua_State>(L,[
        userCount=L->cpp_user_data_->userCount
    ](lua_State * L_) {
        if (L_==nullptr) { return; }
        auto __lock__data__=L_->cpp_user_data_->mutex();
        std::unique_lock<std::recursive_mutex>  _lock_(*(__lock__data__));
        --(*userCount);
        if (*userCount==0) { lua_close(L_);*userCount=-99999; }
    });
}

/*namespace*/
}
}
}

std::shared_ptr<lua_State> LuaUtility::createLuaState() {
    return  __cct::__private::createLuaState();
}
std::shared_ptr<lua_State> LuaUtility::createLuaState(lua_State* L) {
    return __cct::__private::createLuaState(L);
}

namespace {
namespace __cct {
namespace __private {

/* input a table and out put a table */
inline int luaL_copyTable(lua_State * L) {

    if (lua_istable(L,-1)) {
        const auto source_table_top_=lua_gettop(L);

        std::list<int> from_,to_;
        from_.push_back(source_table_top_);
        std::map< const void *,int > all_tables_;

        lua_newtable(L);/*create temp table*/
        const auto temp_table_=lua_gettop(L);

        lua_pushnil(L);
        lua_copy(L,-2,-1);/*copy soure table*/

        lua_newtable(L);
        const auto target_table_=lua_gettop(L);
        to_.push_back(target_table_);/*create target table*/

        lua_pushnil(L);
        lua_pushnil(L);
        lua_copy(L,-4,-2);/*copy soure table*/
        lua_copy(L,-3,-1);/*copy target table*/

        int copy_table_count_=0;

    copy_next_table:
        while (from_.empty()==false) {
            const auto tf_=*from_.crbegin();
            const auto tt_=*to_.crbegin();
            from_.pop_back(); to_.pop_back();

            if (lua_istable(L,-1)) {
                lua_pushnil(L);
            }

            while (lua_next(L,tf_)!=0) {
                /*-1 value -2 key*/
                if (lua_istable(L,-1)) {
                    const void * table_pointer=lua_topointer(L,-1);
                    auto end_=all_tables_.end();
                    auto pos_=all_tables_.find(table_pointer);
                    if (end_!=pos_) {
                        /* copy value has exist */
                        lua_pop(L,1);/*remove old one*/
                        const auto ttt_=pos_->second;
                        lua_pushinteger(L,ttt_);
                        lua_gettable(L,temp_table_);/*set value*/
                        lua_pushnil(L); lua_pushnil(L);
                        lua_copy(L,-3,-1); lua_copy(L,-4,-2);
                        lua_settable(L,tt_);
                        lua_pop(L,1);/*remove the table*/
                    }
                    else {
                        /* copy value not exist */
                        ++copy_table_count_;

                        all_tables_[table_pointer]=copy_table_count_;

                        lua_pushnil(L);
                        lua_pushinteger(L,copy_table_count_);
                        lua_newtable(L);
                        lua_copy(L,-1,-3);

                        /*set temp table*/
                        lua_settable(L,temp_table_);

                        /*set current table to temp table*/
                        lua_pushnil(L); lua_pushnil(L);
                        lua_copy(L,-3,-1); lua_copy(L,-5,-2);
                        lua_settable(L,tt_);

                        from_.push_back(tf_);
                        to_.push_back(tt_);
                        auto ttt_=lua_gettop(L);
                        to_.push_back(ttt_);
                        from_.push_back(ttt_-1);

                        goto copy_next_table;
                    }
                }
                else {
                    /* copy value not table */
                    lua_pushnil(L); lua_pushnil(L);
                    lua_copy(L,-3,-1); lua_copy(L,-4,-2);
                    lua_settable(L,tt_);/*remove key value*/
                    lua_pop(L,1);/*remove key*/
                }
            }/*~while*/

            lua_pop(L,2);/*remove source table , target table*/

        }/*all while*/

         /* return ans */
        lua_copy(L,target_table_,source_table_top_);
        lua_settop(L,source_table_top_);
        return 1;

    }/*~if*/

    /*确保输出一个table*/
    lua_newtable(L);
    return 1;
}

/*namespace*/
}
}
}

namespace {
namespace __cct {
namespace __private {

inline void luaL_printTable(
    lua_State * L,
    std::function<void(const std::string &)> print_
    ) {

    /*suport type*/
    enum DataType : int {
        Bool,Number,Integer,String,NIL
    };

    class Data {
    public:
        Data():type(NIL) {}
        Data(bool i):type(Bool),boolean(i) {}
        Data(lua_Integer i):type(Integer),integer(i) {}
        Data(lua_Number i):type(Number),number(i) {}
        Data(const std::string & i):type(String),string(i) {}
        Data(std::string && i):type(String),string(std::move(i)) {}
        Data(const Data & v):type(v.type) {
            switch (type) {
                case Bool:boolean=v.boolean; break;
                case Number:number=v.number; break;
                case Integer:integer=v.integer; break;
                case String: {new(&string) std::string(v.string); }; break;
                case NIL:; break;
            }
        }

        Data(Data && v):type(v.type) {
            switch (type) {
                case Bool:boolean=v.boolean; break;
                case Number:number=v.number; break;
                case Integer:integer=v.integer; break;
                case String: {new(&string) std::string(std::move(v.string)); }; break;
                case NIL:; break;
            }
        }

        Data & operator=(const Data & v) {
            if (this==&v) { return *this; }
            if (v.type==String) {
                if (type==String) { string=v.string; }
                else {
                    type=String;
                    new (&string) std::string(v.string);
                }
            }
            else {
                if (type==String) {
                    typedef std::string _T_;
                    string.~_T_();
                }
                switch (v.type) {
                    case Bool: {type=Bool; boolean=v.boolean; } break;
                    case Number: {type=Number; number=v.number; }break;
                    case Integer: {type=Integer; integer=v.integer; }break;
                    case String: {}break;
                    case NIL: {type=NIL; }break;
                }
            }

            return *this;
        }

        Data & operator=(Data && v) {
            if (this==&v) { return *this; }
            if (v.type==String) {
                if (type==String) { string=std::move(v.string); }
                else {
                    type=String;
                    new (&string) std::string(std::move(v.string));
                }
            }
            else {
                if (type==String) {
                    typedef std::string _T_;
                    string.~_T_();
                }
                switch (v.type) {
                    case Bool: {type=Bool; boolean=v.boolean; }break;
                    case Number: {type=Number; number=v.number; }break;
                    case Integer: {type=Integer; integer=v.integer; }break;
                    case String: {}break;
                    case NIL: {type=NIL; }break;
                }
            }

            return *this;
        }

        ~Data() {
            if (type==String) { typedef std::string _T_; string.~_T_(); }
        }

        DataType type;
        union {
            bool boolean;
            lua_Number number;
            lua_Integer integer;
            std::string string;
        };
    };

    struct TableMemory {
        Data data;
        int table;
        bool ipair=false;
        lua_Integer ipair_index=1;
        lua_Integer tableIndex=0;
        TableMemory() {}
        TableMemory(const std::string & v,int t):data(v),table(t) {}
        TableMemory(std::string && v,int t):data(std::move(v)),table(t) {}
        TableMemory(std::string && v,int t,bool i,lua_Integer ii,lua_Integer ti):data(std::move(v)),table(t),ipair(i),ipair_index(ii),tableIndex(ti) {}
        TableMemory(Data && v,int t):data(std::move(v)),table(t) {}
        TableMemory(const Data & v,int t):data(v),table(t) {}
        TableMemory(Data && v,int t,bool i,lua_Integer ii,lua_Integer ti):data(std::move(v)),table(t),ipair(i),ipair_index(ii),tableIndex(ti) {}
    };

    const auto is_integer=[](const std::string & v)->bool {
        if (v.empty()) { return false; }
        const auto i=v[0]; if ((i>='0')&&(i<='9')) { return true; }
        return false;
    };

    const auto to_string=[](const auto & i) {
        std::stringstream ss; ss.precision(FLOAT_PRECISION_);
        ss<<i; std::string ans; ss>>ans; return std::move(ans);
    };

    const auto oprint_key=[&print_,&to_string,&is_integer](const Data & v) {
        const int & type=v.type;
        switch (type) {
            case DataType::Number: { print_("["); print_(to_string(v.number)); print_("]"); }; break;
            case DataType::Integer: { print_("["); print_(to_string(v.integer)); print_("]"); }; break;
            case DataType::String:
                if (is_integer(v.string)) {
                    print_("[\""); print_(v.string); print_("\"]");
                }
                else {
                    print_(v.string);
                }break;
        }
    };

    const auto string_find=[](const std::string & s,const auto & v) {return (s.find(v)!=s.npos); };

    const auto oprint_value=[&print_,&to_string,&string_find](const Data & v) {
        const DataType & type=v.type;
        switch (type) {
            case DataType::Bool: { if (v.boolean) { print_("true"); } else { print_("false"); } }break;
            case DataType::Number: {  print_(to_string(v.number));  }; break;
            case DataType::Integer: { print_(to_string(v.integer));  }; break;
            case DataType::String: {
                std::string op_="==";
                while ((string_find(v.string,"["+op_+"["))||string_find(v.string,"]"+op_+"]")) { op_+="==="; }
                print_("["+op_+"[");
                print_(v.string);
                print_("]"+op_+"]");
            }; break;
            case DataType::NIL: {print_("nil"); }  break;
        }
    };

    const auto print_endl=[&print_]() {print_("\n"); };
    const auto print_line_endl=[&print_]() {print_(" ;  \n"); };
    const auto print_file_begin=[&print_](const std::string & tbname) {
        print_(tbname);
        print_(" = (function()                    \n\nlocal ");
    };

    const auto print_file_end=[&print_](const std::string & tbname) {
        print_("\nreturn "+tbname);
        print_("; end)()");
    };

    const auto table_name_full=[&to_string](const std::list< TableMemory > & tables,const Data & ctable)->std::string {
        auto root_name_=tables.begin();
        auto end_name_=tables.end();
        std::string ans;
        ans=root_name_->data.string;
        for (auto next_name_=root_name_; (++next_name_)!=end_name_; ) {
            const auto &current_table_name=(*next_name_).data;
            switch (int(current_table_name.type)) {
                case DataType::Integer: ans+=std::move("["+to_string(current_table_name.integer)+"]"); break;
                case DataType::Number: ans+=std::move("["+to_string(current_table_name.number)+"]"); ; break;
                case DataType::String: ans+=std::move("[\""+current_table_name.string+"\"]"); break;
            }
        }
        const auto &current_table_name=ctable;
        switch (int(current_table_name.type)) {
            case DataType::Integer: ans+=std::move("["+to_string(current_table_name.integer)+"]"); break;
            case DataType::Number: ans+=std::move("["+to_string(current_table_name.number)+"]"); ; break;
            case DataType::String: ans+=std::move("[\""+current_table_name.string+"\"]"); break;
        }
        return std::move(ans);
    };

    /*-----------------------------------------------*/
    if (lua_gettop(L)<2) { lua_pushstring(L,"you must input table name and table"); lua_error(L); }
    if (lua_isstring(L,1)==false) { lua_pushstring(L,"table name must a string"); lua_error(L); }
    if (lua_istable(L,2)==false) { lua_pushstring(L,"you must input a table"); lua_error(L); }

    /* copy the table twice */
    lua_pushvalue(L,2);
    lua_pushvalue(L,2);

    const std::string tbname(lua_tostring(L,1));
    print_file_begin(tbname);

    /*-----------------------------------------------*/
    lua_Integer table_index_=0;
    std::list< TableMemory > print_tables{ {tbname, 2} };
    std::list< std::string > final_print_lines;
    std::map< const void *,std::string > all_tables{ {lua_topointer(L,2),tbname} };

print_next_start:
    while (print_tables.empty()==false) {

        auto & current_table_memory=*print_tables.rbegin();
        int current_table=current_table_memory.table;/*the table in the lua state*/
        Data current_table_name=std::move(current_table_memory.data);/*the table name */
        bool ipair_=current_table_memory.ipair;/*the value will be true if the index follow 1,2,3....  */
        lua_Integer ipair_index_=current_table_memory.ipair_index;/*current index if ipair is true*/
        lua_Integer current_table_index=current_table_memory.tableIndex;/*the table index in this function */

        print_tables.pop_back();

        /* reset the value : ipair_ */
        if (lua_istable(L,-1)) {

            const static constexpr char start_string[]{ "{   " };
            switch (int(current_table_name.type)) {
                case DataType::Integer:if (false==ipair_) { print_("["+to_string(current_table_name.integer)+"] ="); }print_(start_string); break;
                case DataType::Number: if (false==ipair_) { print_("["+to_string(current_table_name.number)+"] ="); }print_(start_string); break;
                case DataType::String: {
                    if (is_integer(current_table_name.string)) {
                        print_("[\""+current_table_name.string+"\"] ="+start_string);
                    }
                    else {
                        print_(current_table_name.string);
                        print_(" =");
                        print_(start_string);
                    }
                } break;
            }

            lua_pushnil(L);
            ipair_=true;
            print_("--[[ "+to_string(current_table_index)+" --]]  \n");

        }

        while (lua_next(L,current_table)!=0) {
            /* uses 'key' (at index -2) and 'value' (at index -1) */
            if (lua_istable(L,-1)) {

                Data key_;
                auto type_=lua_type(L,-2);
                switch (type_) {
                    case LUA_TSTRING:ipair_=false; key_=std::string(lua_tostring(L,-2));  break;
                    case LUA_TNUMBER: {
                        key_=lua_tointeger(L,-2);
                        if (ipair_) {
                            if (key_.integer==ipair_index_) {
                                ++ipair_index_;
                            }
                            else {
                                ipair_=false;
                            }
                        } } break;
                    default: lua_pushstring(L,"key must be number or string"); lua_error(L); ; break;
                }

                const void * table_pointer=lua_topointer(L,-1);
                auto ctable=all_tables.find(table_pointer);
                const auto etable=all_tables.end();

                if (ctable==etable) {
                    /*find a new table*/
                    ++table_index_;
                    /*save old value*/
                    print_tables.emplace_back(std::move(current_table_name),current_table,ipair_,ipair_index_,current_table_index);

                    all_tables.insert({ table_pointer,table_name_full(print_tables ,key_) });

                    current_table=lua_gettop(L);
                    current_table_name=std::move(key_);

                    /*set new value*/
                    print_tables.emplace_back(std::move(current_table_name),current_table,ipair_,1,table_index_);

                    goto print_next_start;
                }
                else {
                    /*circle table*/

                    lua_pop(L,1);/*pop the table*/
                    ipair_=false;/*circle table do not surport ipair*/

                    print_tables.emplace_back(std::move(current_table_name),-1);
                    auto this_table_name_=table_name_full(print_tables,key_);

                    current_table_name=std::move((*print_tables.rbegin()).data);
                    print_tables.pop_back();

                    final_print_lines.push_back(std::move(this_table_name_)+" = "+ctable->second+"\n");
                }

            }
            else {
                Data key_,value_;
                bool do_not_support=false;
                auto type_=lua_type(L,-2);
                switch (type_) {
                    case LUA_TSTRING: ipair_=false; key_=std::string(lua_tostring(L,-2));  break;
                    case LUA_TNUMBER: {key_=lua_tointeger(L,-2);
                        if (ipair_) {
                            if (key_.integer==ipair_index_) {
                                ++ipair_index_;
                            }
                            else {
                                ipair_=false;
                            }
                        }
                    } break;
                    default: lua_pushstring(L,"key must be number or string"); lua_error(L); ; break;
                }

                type_=lua_type(L,-1);
                switch (type_) {
                    case LUA_TNIL: break;
                    case LUA_TBOOLEAN: value_=bool(lua_toboolean(L,-1)); break;
                    case LUA_TSTRING: value_=std::string(lua_tostring(L,-1)); break;
                    case LUA_TNUMBER: value_=lua_tonumber(L,-1); break;
                    case LUA_TFUNCTION: value_=std::string("function() end"); break;
                    default: do_not_support=true; break;
                }

                if (do_not_support) { lua_pop(L,1); continue; }

                if (false==ipair_) {
                    oprint_key(key_);
                    print_(" = ");
                }
                oprint_value(value_);
                print_line_endl();

                lua_pop(L,1);
            }
        }/*while table*/

        if (print_tables.empty()) {
            print_("} --[[ "+to_string(current_table_index)+" --]] \n");
        }
        else {
            print_("} , --[[ "+to_string(current_table_index)+" --]] \n");
        }

        lua_pop(L,1);
    }

    if (false==final_print_lines.empty()) {
        print_endl();
        for (const auto & line:final_print_lines) {
            print_(line);
        }
    }

    print_file_end(tbname);

    print_endl();
    print_("--[[***********************--]]\n");
    print_endl();

    return;
}

/*namespace*/
}
}
}

int LuaUtility::copyTable(lua_State *L) {
    if (L==nullptr) { return 0; }
    return __cct::__private::luaL_copyTable(L);
}

void LuaUtility::printTable(
        lua_State *L,
        std::function<void(const std::string &)> print_) {
    return __cct::__private::luaL_printTable(L,std::move(print_));
}

int LuaUtility::showTable(lua_State * L) {
    if (L==nullptr) { return 0; }
    printTable(L,[](const std::string & str) {
        std::cout<<str;
    });
    std::cout.flush();
    return 0;
}

int LuaUtility::tableToString(lua_State * L) {
    if (L==nullptr) { return 0; }
    std::list<std::string> tmp_;
    std::string::size_type length_=0;
    printTable(L,[&tmp_,&length_](const std::string & str) {
        length_+=(str.size()+1);
        tmp_.push_back(str);
    });

    {
        std::unique_ptr<luaL_Buffer> buffer__(new luaL_Buffer);
        register luaL_Buffer & buffer_=*buffer__;
        luaL_buffinitsize(L,&buffer_,length_);
        while (tmp_.empty()==false) {
            std::string str=std::move(*tmp_.begin());
            tmp_.pop_front();
            luaL_addlstring(&buffer_,str.c_str(),str.size());
        }
        luaL_pushresult(&buffer_);
    }

    return 1;
}

namespace {
template<typename _QIODevice_>
void _p_loadFile_read(
    _QIODevice_ & zFile,
    luaL_Buffer & _v_buffer
    ) {
    enum { SIZE_=1024*4 };
    std::unique_ptr<char,void(*)(char *)> __data
        (new char[SIZE_+8],[](char * _d) {delete[] _d; });
    __data.get()[0]=0; 
    __data.get()[1]=0; 
    __data.get()[2]=0;
    __data.get()[SIZE_]=0;
    __data.get()[SIZE_+1]=0;
    __data.get()[SIZE_+2]=0;
    __data.get()[SIZE_+3]=0;
    auto size__=zFile.read(__data.get(),SIZE_);

    /*加载第一段数据*/
    /*-bom :0xEF0xBB0xBF*/
    if (
        (__data.get()[0])==char(0x00ef)&&
        (__data.get()[1])==char(0x00bb)&&
        (__data.get()[2])==char(0x00bf)&&
        size__>3
        ) {
        luaL_addlstring(&_v_buffer,__data.get()+3,size__-3);
    }
    else {
        luaL_addlstring(&_v_buffer,__data.get(),size__ );
    }

    while ((size__=zFile.read(__data.get(),SIZE_))>0) {
        luaL_addlstring(&_v_buffer,__data.get(),size__);
    }
}

}

template<typename _T_,typename _U_>
inline int LuaUtility::_p_loadFile(
    lua_State * L,
    _T_ && _a_fileName_,
    _U_ && _a_zip_file_name_
    ) {

    const auto top_lock_=lua_gettop(L);
    bool _is_Ok_=true;

    /*load string*/
    try {

        const QString _a_fileName=_a_fileName_.trimmed();
        const QString _a_zip_file_name=_a_zip_file_name_.trimmed();

        if (_a_fileName.isEmpty()) { return 0; }

        auto _v__buffer
            =std::shared_ptr<luaL_Buffer>(
                new luaL_Buffer,
                [L](luaL_Buffer * _buffer_) {
            luaL_pushresult(_buffer_);
            delete _buffer_;
        }
        );

        auto & _v_buffer=*_v__buffer;

        luaL_buffinit(L,&_v_buffer);

        if (_a_fileName.endsWith(".zip",Qt::CaseInsensitive)) {
            QuaZip zip_file_(_a_fileName);
            if (zip_file_.open(QuaZip::mdUnzip)) {
                if (zip_file_.setCurrentFile(_a_zip_file_name)) {
                    QuaZipFile zFile(&zip_file_);
                    if (zFile.open(QIODevice::ReadOnly)) {
                        _p_loadFile_read(zFile,_v_buffer);
                    }
                    else {
                        qDebug().noquote()<<"can not open zipfile"<<_a_zip_file_name;
                        throw nullptr;
                    }
                }
                else {
                    qDebug().noquote()<<"can not find zipfile"<<_a_zip_file_name;
                    throw nullptr;
                }
            }
            else {
                qDebug().noquote()<<"can not open file"<<_a_fileName;
                throw nullptr;
            }

        }
        else {
            QFile file_(_a_fileName);
            if (file_.open(QIODevice::ReadOnly)) {
                _p_loadFile_read(file_,_v_buffer);
            }
            else {
                qDebug().noquote()<<"can not open file"<<_a_fileName;
                throw nullptr;
            }
        }

    }
    catch (...) {
        _is_Ok_=false;
    }

    if (_is_Ok_) {
        size_t __size__;
        const char * __string__=lua_tolstring(L,-1,&__size__);
        if( luaL_loadbuffer(L,__string__,__size__,__string__) == LUA_OK ){
            assert( (lua_gettop(L)-top_lock_)==2 );
            lua_copy(L,-1,-2);
            lua_settop(L,top_lock_+1);
            return 1;
        }
        else {
            const char * _error_=luaL_tolstring(L,-1,&__size__);
            if ( __size__ && _error_ ) {
                qDebug()<<"error on build "<<QByteArray(_error_,__size__);
            }
            lua_settop(L,top_lock_);
            return 0;
        }
    }
    else {
        lua_settop(L,top_lock_);
        return 0;
    }

    return 1;
}

int LuaUtility::loadFile(
    lua_State * const L,
    const QString & a,
    const QString & b
    ) {
    if (L)return _p_loadFile(L,a,b);
    return 0;
}

int LuaUtility::loadFile(
    lua_State * const L,
    QString && _a_fileName,
    QString && b
    ) {
    if (L)return _p_loadFile(L,std::move(_a_fileName),std::move(b));
    return 0;
}

int LuaUtility::loadFile(
    lua_State * const L,
    QString && a,
    const QString & b) {
    if (L)return _p_loadFile(L,std::move(a),b);
    return 0;
}

int LuaUtility::loadFile(
    lua_State * const L,
    const QString & a,
    QString && b) {
    if (L)return _p_loadFile(L,a,std::move(b));
    return 0;
}

int LuaUtility::openLib(lua_State * L) {
    constexpr const static struct luaL_Reg libs_[]{
        {"copyTable",&LuaUtility::copyTable},
        {"showTable",&LuaUtility::showTable},
        {"tableToString",&LuaUtility::tableToString},
        {nullptr,nullptr}
    };

    luaL_newlib(L,libs_);

    return 1;
}

void LuaUtility::loadModule(lua_State * L) {
    luaL_requiref(L,"utility",&LuaUtility::openLib,1);
    lua_pop(L,1);  /* remove lib */
    return;
}

/*
 * 扩展LUA
 * 此文件应当采用utf8 with bom 编码
 * Final
*/



