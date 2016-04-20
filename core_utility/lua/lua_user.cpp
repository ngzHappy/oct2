//#define DEBUG_THIS_FILE
#define LUA_LIB
#include "lua_user.hpp"
#include "lstate.h"
#include "llimits.h"
#include "lua.hpp"
#if defined(DEBUG_THIS_FILE)
#include <iostream>
#endif

namespace __private__lua{

#if defined(DEBUG_THIS_FILE)
static int test_count_=0;
#endif

LuaUserData::LuaUserData(){
    mutex_=std::make_shared<std::recursive_mutex>();
    userCount=std::make_shared<int>(0);
#if defined(DEBUG_THIS_FILE)
    std::cout<<"??test"<<test_count_<<std::endl;
    ++test_count_;
#endif
}

LuaUserData::LuaUserData(
    const std::shared_ptr<std::recursive_mutex> &u
) {
    mutex_=u;
    userCount=std::make_shared<int>(0);
#if defined(DEBUG_THIS_FILE)
    std::cout<<"??test"<<test_count_<<std::endl;
    ++test_count_;
#endif
}

LuaUserData::~LuaUserData(){
#if defined(DEBUG_THIS_FILE)
    --test_count_;
    std::cout<<"??~test"<<test_count_<<std::endl;
#endif
}

extern void _lua_lock(lua_State *L) {
    L->cpp_user_data_->lock();
}

extern void _lua_unlock(lua_State *L) {
    L->cpp_user_data_->unlock();
}

extern void _luai_userstatethread(
    lua_State *L,
    lua_State *L1){
    /*
    每个thread都共享global_State,
    所以必须用同一个锁
    */
    L1->cpp_user_data_=new LuaUserData(L->cpp_user_data_->mutex());
    (void)L;
}

extern void _luai_userstatefree(
    lua_State *L,
    lua_State *L1) {
    delete L1->cpp_user_data_;
    (void)L;
}

extern void _luai_userstateopen(lua_State *L) {
    L->cpp_user_data_=new LuaUserData;
}

extern void _luai_userstateclose(lua_State *L) {
    auto lock_=L->cpp_user_data_->mutex();
    delete L->cpp_user_data_;
    lock_->unlock();
}

}


