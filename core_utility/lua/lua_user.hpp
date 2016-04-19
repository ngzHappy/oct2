#ifndef __USER__LUA__HPP__0x00
#define __USER__LUA__HPP__0x00

#include <memory>
#include <mutex>

namespace __private__lua{
class LuaUserData {
    std::shared_ptr<std::recursive_mutex> mutex_;
    
public:
    LuaUserData();
    ~LuaUserData();

    void lock() { mutex_->lock();}
    void unlock() {mutex_->unlock();}
    std::shared_ptr<std::recursive_mutex> mutex() const { return mutex_; }
    int userCount{ 0 };
};
}

#endif


