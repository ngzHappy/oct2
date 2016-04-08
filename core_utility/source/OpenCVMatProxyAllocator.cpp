#include "../OpenCVMatProxyAllocator.hpp"
#include <QtCore/qdebug.h>

using namespace _OPENCV_StdMatAllocator;
cv::UMatData* __private::StdMatAllocator::allocate_user_data(void * _a_data_) {
    using namespace cv;
    assert(_a_data_);
    UMatData* const ans_=
        StdMatAllocator::allocate(
            0,nullptr,0,
            _a_data_/*此数据仅仅用于初始化UMatData::USER_ALLOCATED*/,
            nullptr,
            0,cv::USAGE_DEFAULT);
    ans_->userdata=_a_data_/*设置析构数据*/;
    ans_->refcount=1/*设置引用计数*/;
    return ans_;
}

bool __private::StdMatAllocator::allocate(
    cv::UMatData* u,
    int /*accessFlags*/,
    cv::UMatUsageFlags /*usageFlags*/) const {
    if (!u) return false;
    return true;
}

void __private::StdMatAllocator::deallocate(cv::UMatData* u) const {
    using namespace cv;
    if (!u)
        return;

    CV_Assert(u->urefcount==0);
    CV_Assert(u->refcount==0);
    if (!(u->flags & UMatData::USER_ALLOCATED)) {
        fastFree(u->origdata);
        u->origdata=0;
    }
    delete u;
}

cv::UMatData* __private::StdMatAllocator::allocate(
    int dims,const int* sizes,
    int type,void* data0,
    size_t* step,int /*flags*/,
    cv::UMatUsageFlags /*usageFlags*/) const {
    using namespace cv;
    size_t total=CV_ELEM_SIZE(type);
    for (int i=dims-1; i>=0; i--) {
        if (step) {
            if (data0 && step[i]!=CV_AUTOSTEP) {
                CV_Assert(total<=step[i]);
                total=step[i];
            }
            else
                step[i]=total;
        }
        total*=sizes[i];
    }
    uchar* data=data0?(uchar*)data0:(uchar*)fastMalloc(total);
    UMatData* u=new UMatData(this);
    u->data=u->origdata=data;
    u->size=total;
    if (data0)
        u->flags|=UMatData::USER_ALLOCATED;

    return u;
}

cv::UMatData* OpenCVUserDataAllocator::allocate(void * data_,DestoryFunction fun_) {
    DestoryType * _d=new DestoryType(data_,fun_);
    return allocate_user_data(_d);
}

void OpenCVUserDataAllocator::deallocate(cv::UMatData* data) const {
    //std::cout<<"delete data"<<std::endl;
    assert(data->userdata);
    delete reinterpret_cast<DestoryType *>(data->userdata);
    return OpenCVMatProxyAllocator::deallocate(data);
}

OpenCVUserDataAllocator * OpenCVUserDataAllocator::instance() {
    static OpenCVUserDataAllocator * ans_=nullptr;
    if (ans_) { return ans_; }
    ans_=new OpenCVUserDataAllocator();
    qAddPostRoutine([]() {
        OpenCVUserDataAllocator * ans_temp_=ans_;
        ans_=nullptr;
        delete ans_temp_; });
    return ans_;
}

