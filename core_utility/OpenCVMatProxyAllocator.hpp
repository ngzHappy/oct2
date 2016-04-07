#ifndef OPENCVMATPROXYALLOCATOR_HPP
#define OPENCVMATPROXYALLOCATOR_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include "OpenCVUtility.hpp"

namespace _OPENCV_StdMatAllocator {
namespace __private {

class CORE_UTILITYSHARED_EXPORT StdMatAllocator : public cv::MatAllocator {
public:
    StdMatAllocator()=default;
    ~StdMatAllocator()=default;
    cv::UMatData* allocate_user_data(void * _a_data_);
    cv::UMatData* allocate(
        int dims,const int* sizes,
        int type,void* data0,
        size_t* step,int /*flags*/,
        cv::UMatUsageFlags /*usageFlags*/) const override;
    bool allocate(cv::UMatData* u,int /*accessFlags*/,cv::UMatUsageFlags /*usageFlags*/) const override;
    void deallocate(cv::UMatData* u) const override;
};
}
}

class CORE_UTILITYSHARED_EXPORT OpenCVMatProxyAllocator :
    public _OPENCV_StdMatAllocator::__private::StdMatAllocator {
public:
};

class CORE_UTILITYSHARED_EXPORT OpenCVUserDataAllocator :
    public OpenCVMatProxyAllocator {
    OpenCVUserDataAllocator():OpenCVMatProxyAllocator() {}
public:
    typedef void(*DestoryFunction)(void*);
    class DestoryType {
        DestoryType&operator=(const DestoryType &)=delete;
        DestoryType&operator=(DestoryType&&)=delete;
        DestoryType(const DestoryType &)=delete;
        DestoryType(DestoryType&&)=delete;
    public:
        void * const data;
        DestoryFunction function;
        DestoryType(void * data_,DestoryFunction function_):data(data_),function(function_) {}
        DestoryType(DestoryFunction function_,void * data_):data(data_),function(function_) {}
        ~DestoryType() { if (function) { function(data); } }
    };

    static OpenCVUserDataAllocator * instance();
    cv::UMatData* allocate(void * data_,DestoryFunction fun_);
    cv::UMatData* allocate(DestoryFunction fun_,void * data_) { return allocate(data_,fun_); }
    void deallocate(cv::UMatData* data) const override;
};


#endif // OPENCVMATPROXYALLOCATOR_HPP
