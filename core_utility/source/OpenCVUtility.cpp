#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#include "../OpenCVUtility.hpp"
#include "../OpenCVException.hpp"
#include <QtWidgets/qapplication.h>
#include <QtGui/qimage.h>
#include <QtCore/qtimer.h>
#include <private/qimage_p.h>
#include <QtGui/qimagereader.h>
#include <QtCore/qdebug.h>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <cassert>

OpenCVUtility::OpenCVUtility(QObject * p):QObject(p) {}

OpenCVUtility::~OpenCVUtility() {}

void OpenCVUtility::construct() {
}

namespace {

void deleteAny(QVariant * data_) {
    delete data_;
}

class StdMatAllocator : public cv::MatAllocator {
public:
    cv::UMatData* allocate(
        int dims,
        const int* sizes,
        int type,
        void* data0,
        size_t* step,
        int /*flags*/,
        cv::UMatUsageFlags /*usageFlags*/) const {

        using namespace cv;
        size_t total=CV_ELEM_SIZE(type);
        for (int i=dims-1; i>=0; i--) {
            if (step) {
                if (data0 && step[i]!=CV_AUTOSTEP) {
                    CV_Assert(total<=step[i]);
                    total=step[i];
                }
                else {
                    step[i]=total;
                }
            }
            total*=sizes[i];
        }

        uchar* data=data0?(uchar*)data0:(uchar*)fastMalloc(total);
        UMatData* u=new UMatData(this);
        u->data=u->origdata=data;
        u->size=total;
        if (data0) { u->flags|=UMatData::USER_ALLOCATED; }

        return u;
    }

    bool allocate(
        cv::UMatData* u,
        int /*accessFlags*/,
        cv::UMatUsageFlags /*usageFlags*/) const {
        if (!u) return false;
        return true;
    }

    void deallocate(cv::UMatData* u) const {
        using namespace cv;
        if (!u) return;

        CV_Assert(u->urefcount==0);
        CV_Assert(u->refcount==0);

        if (!(u->flags & UMatData::USER_ALLOCATED)) {
            fastFree(u->origdata);
            u->origdata=0;
        }

        if (u->userdata) {
            //assert( u->handle == &deleteAny );
            deleteAny(reinterpret_cast<QVariant *>(u->userdata));
            //#if defined(_DEBUG)
            //            qDebug()<<"destory qimage "<<__func__;
            //#endif
        }

        delete u;
    }
};

}

namespace {
static cv::MatAllocator * stdMalloc=nullptr;
}

cv::MatAllocator * OpenCVUtility::getReaderAllocator() {
    if (stdMalloc) { return stdMalloc; }
    stdMalloc=new StdMatAllocator;
    qAddPostRoutine([]() {
        delete stdMalloc;
        stdMalloc=0;
    });
    return stdMalloc;
}

namespace {

static inline void __construct() {
    {   /*强制加载图片插件,加强运行期体验*/
        QImage * image_=new QImage(":/i_m_a_g_e_s_/images/000000.png");
        auto width_=image_->width(); (void)width_;
        auto height_=image_->height(); (void)height_;
        assert(width_>0);
        assert(height_>0);
        delete image_;
    }
    {
        /*设置随机种子*/
        std::srand(int(std::time(nullptr)));
    }
    OpenCVUtility::construct();
}
}

OpenCVUtility::Handle OpenCVUtility::getHandle() {
    return &deleteAny;
}

namespace {
QImage::Format format_change_(QImage::Format format_) {
    QImage::Format & image_=format_;
    switch (format_) {
        case QImage::Format_Invalid:break;
        case QImage::Format_Mono:break;
        case QImage::Format_MonoLSB:break;
        case QImage::Format_Indexed8:{
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_RGB32: {
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_ARGB32: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_ARGB32_Premultiplied: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_RGB16: {
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_ARGB8565_Premultiplied: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_RGB666: {
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_ARGB6666_Premultiplied: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_RGB555: {
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_ARGB8555_Premultiplied: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_RGB888: break;
        case QImage::Format_RGB444: {
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_ARGB4444_Premultiplied: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_RGBX8888: {
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_RGBA8888: {}break;
        case QImage::Format_RGBA8888_Premultiplied: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_BGR30: {
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_A2BGR30_Premultiplied: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_RGB30: {
            image_=QImage::Format_RGB888;
        }break;
        case QImage::Format_A2RGB30_Premultiplied: {
            image_=QImage::Format_RGBA8888;
        }break;
        case QImage::Format_Alpha8:break;
        case QImage::Format_Grayscale8:break;
        case QImage::NImageFormats:break;
        default:break;
    }
    return format_;
}
}

cv::Mat OpenCVUtility::read(const QString & string_) {
    QImage image_(string_);
    return read(image_);
}

cv::Mat OpenCVUtility::read(const QImage & image__) {
    if (image__.width()<=0) { return cv::Mat(); }
    if (image__.height()<=0) { return cv::Mat(); }

    /*add a ref*/
    QImage image_=image__;

    QImage::Format format_=image_.format();
    format_=format_change_(format_);
    image_=image_.convertToFormat(format_);
    format_=image_.format();

    /*创建数据的独立副本*/
    //image_.detach();

    if (format_==QImage::Format_RGB888) {
        cv::Mat xmat_(
            image_.height(),
            image_.width(),
            CV_8UC3,
            const_cast<uchar *>(image_.constBits()),
            image_.bytesPerLine()
            );
        assert(xmat_.u==nullptr);
        assert(xmat_.data);
        xmat_.u=getReaderAllocator()
            ->allocate(0,nullptr,0,xmat_.data,nullptr,0,cv::USAGE_DEFAULT);
        assert(xmat_.u->currAllocator==getReaderAllocator());
        assert(xmat_.u->userdata==nullptr);
        assert(xmat_.u->handle==nullptr);
        //xmat_.u->handle = reinterpret_cast<void *>( OpenCVUtility::getHandle() );
        xmat_.u->userdata=new QVariant(QImage(std::move(image_)));
        xmat_.u->refcount=1;
        return std::move(xmat_);
    }
    else if (format_==QImage::Format_RGBA8888) {
        cv::Mat xmat_(
            image_.height(),
            image_.width(),
            CV_8UC4,
            const_cast<uchar *>(image_.constBits()),
            image_.bytesPerLine()
            );
        assert(xmat_.u==nullptr);
        assert(xmat_.data);
        xmat_.u=getReaderAllocator()
            ->allocate(0,nullptr,0,xmat_.data,nullptr,0,cv::USAGE_DEFAULT);
        assert(xmat_.u->currAllocator==getReaderAllocator());
        assert(xmat_.u->userdata==nullptr);
        assert(xmat_.u->handle==nullptr);
        //xmat_.u->handle= reinterpret_cast<void *>(OpenCVUtility::getHandle());
        xmat_.u->userdata=new QVariant(QImage(std::move(image_)));
        xmat_.u->refcount=1;
        return std::move(xmat_);
    }
    else {
        if (format_==QImage::Format_Grayscale8) {
            cv::Mat xmat_(
                image_.height(),
                image_.width(),
                CV_8UC1,
                const_cast<uchar *>(image_.constBits()),
                image_.bytesPerLine()
                );
            assert(xmat_.u==nullptr);
            assert(xmat_.data);
            xmat_.u=getReaderAllocator()
                ->allocate(0,nullptr,0,xmat_.data,nullptr,0,cv::USAGE_DEFAULT);
            assert(xmat_.u->currAllocator==getReaderAllocator());
            assert(xmat_.u->userdata==nullptr);
            assert(xmat_.u->handle==nullptr);
            //xmat_.u->handle= reinterpret_cast<void *>(OpenCVUtility::getHandle());
            xmat_.u->userdata=new QVariant(QImage(std::move(image_)));
            xmat_.u->refcount=1;
            return std::move(xmat_);
        }
        else {
            return cv::Mat();
        }
    }

}

namespace {
void handle_qimage_(void * v) {
    delete reinterpret_cast<cv::Mat *>(v);
}
}

OpenCVUtility::HandleQImage OpenCVUtility::getHandleQImage() {
    return &handle_qimage_;
}

cv::Mat OpenCVUtility::read(QImage && v) {
    const QImage value_(std::move(v));
    return read(value_);
}

QImage OpenCVUtility::read(cv::Mat && v) {
    const cv::Mat value_(std::move(v));
    return read(value_);
}

QImage OpenCVUtility::getInnerQImage(cv::Mat && v) {
    const cv::Mat value_(std::move(v));
    return getInnerQImage(value_);
}

cv::Mat OpenCVUtility::getInnerOpenCVMat(QImage && v) {
    const QImage value_(std::move(v));
    return getInnerOpenCVMat(value_);
}

cv::Mat OpenCVUtility::getInnerOpenCVMat(const QImage & image_) {
    QImage::DataPtr data_=const_cast<QImage &>(image_).data_ptr();
    if (data_) {
        if (data_->cleanupInfo) {
            if (data_->cleanupFunction==getHandleQImage()) {
                return *(reinterpret_cast<cv::Mat *>(data_->cleanupInfo));
            }
        }
    }
    return cv::Mat();
}

QImage OpenCVUtility::read(const cv::Mat & v) {
    {
        const cv::Mat & tmp=v;
        if (v.type()==CV_8UC1) {
            if (tmp.cols>0&&tmp.rows>0)
                return QImage(
                    tmp.data,
                    tmp.cols,tmp.rows,
                    tmp.step,
                    QImage::Format_Grayscale8,
                    OpenCVUtility::getHandleQImage(),
                    new cv::Mat(tmp)
                    );
            else return QImage();
        }
        else if (v.type()==CV_8UC3) {
            if (tmp.cols>0&&tmp.rows>0)
                return QImage(
                    tmp.data,
                    tmp.cols,tmp.rows,
                    tmp.step,
                    QImage::Format_RGB888,
                    OpenCVUtility::getHandleQImage(),
                    new cv::Mat(tmp)
                    );
            else return QImage();
        }
        else if (v.type()==CV_8UC4) {
            if (tmp.cols>0&&tmp.rows>0)
                return QImage(
                    tmp.data,
                    tmp.cols,tmp.rows,
                    tmp.step,
                    QImage::Format_RGBA8888,
                    OpenCVUtility::getHandleQImage(),
                    new cv::Mat(tmp)
                    );
            else return QImage();
        }
    }

    cv::Mat tmp;
    const auto channels_=v.channels();
    if (channels_==1) {
        v.convertTo(tmp,CV_8UC1);
        if (tmp.cols>0&&tmp.rows>0) {
            return QImage(
                        tmp.data,
                        tmp.cols,tmp.rows,
                        tmp.step,
                        QImage::Format_Grayscale8,
                        OpenCVUtility::getHandleQImage(),
                        new cv::Mat(tmp)
                        );
        }
    }
    else if (channels_==3) {
        v.convertTo(tmp,CV_8UC3);
        if (tmp.cols>0&&tmp.rows>0)
            return QImage(
                        tmp.data,
                        tmp.cols,tmp.rows,
                        tmp.step,
                        QImage::Format_RGB888,
                        OpenCVUtility::getHandleQImage(),
                        new cv::Mat(tmp)
                        );
    }
    else if (channels_==4) {
        v.convertTo(tmp,CV_8UC4);
        if (tmp.cols>0&&tmp.rows>0)
            return QImage(
                        tmp.data,
                        tmp.cols,tmp.rows,
                        tmp.step,
                        QImage::Format_RGBA8888,
                        OpenCVUtility::getHandleQImage(),
                        new cv::Mat(tmp)
                        );
    }
    return QImage();
}

QImage OpenCVUtility::getInnerQImage(const cv::Mat & v) {
    if ((v.u)&&(v.u->currAllocator==getReaderAllocator())) {
        if (v.u->userdata) {
            //assert( v.u->handle == OpenCVUtility::getHandle() );
            return reinterpret_cast<QVariant *>(v.u->userdata)->value<QImage>();
        }
    }
    return QImage();
}

cv::Mat OpenCVUtility::tryRead(QImage && v) {
    const QImage image_(std::move(v));
    return tryRead(image_);
}

cv::Mat OpenCVUtility::tryRead(const QImage & v) {
    if (v.width()<=0) { return cv::Mat(); }
    if (v.height()<=0) { return cv::Mat(); }

    cv::Mat ans_=getInnerOpenCVMat(v);

    if (ans_.rows<=0||ans_.cols<=0) {
        return read(v);
    }
    return std::move(ans_);
}

QImage OpenCVUtility::tryRead(cv::Mat && v) {
    const cv::Mat value_(std::move(v));
    return tryRead(value_);
}

QImage OpenCVUtility::tryRead(const cv::Mat & v) {
    if (v.rows<=0) { return QImage(); }
    if (v.cols<=0) { return QImage(); }

    QImage ans_=getInnerQImage(v);

    if (ans_.width()<=0||ans_.height()<=0) {
        return read(v);
    }

    /*roi*/
    if ((ans_.width()!=v.cols)||
        (ans_.height()!=v.rows)) {
        return read(v);
    }

    return std::move(ans_);
}

namespace opencv_exception {

class _Static_Data{
public:
    ErrorCallBackFunction efunction_ = nullptr;
    std::shared_ptr<const void> efunction_data_;
    const std::shared_ptr<std::recursive_mutex> mutex_;
    _Static_Data():mutex_(new std::recursive_mutex) {}
};

std::shared_ptr< _Static_Data >  _data_  ;

std::pair<ErrorCallBackFunction,std::shared_ptr<const void>> set_error_function(
        ErrorCallBackFunction e,
    std::shared_ptr<const void> v
        ){
    auto ans___=get_error_function();
    auto data_=_data_;
    if (data_==nullptr) {
        _data_=std::make_shared<_Static_Data>();
        data_= _data_ ;
        qAddPostRoutine([]() {
            auto old_=_data_;
            if (old_) {
                auto mutex__=old_->mutex_;
                {
                    std::unique_lock<std::recursive_mutex> _l(*(old_->mutex_));
                    _data_.reset();
                }
            }
        });
    }
    auto mutex__=data_->mutex_;
    {
        std::unique_lock<std::recursive_mutex> _l(*(data_->mutex_));
        data_->efunction_=e;
        data_->efunction_data_=std::move(v);
    }
    return std::move(ans___);
}

void error(
    const cv::Exception & e,
    const std::string & _what,
    std::size_t _Line,
    const char * _File,
    const char * _Func){
    auto data_=_data_;
    if (data_) {
        auto mutex__=data_->mutex_;
        {
            std::unique_lock<std::recursive_mutex> _l(*(mutex__));
            if (data_->efunction_) {
                data_->efunction_(e,
                    _what,_Line,_File,_Func,
                    data_->efunction_data_);
            }
        }
    }
}

std::pair<ErrorCallBackFunction,std::shared_ptr<const void>>
get_error_function(){
    auto data_=_data_;
    if (data_==nullptr) {
        return std::pair<ErrorCallBackFunction,std::shared_ptr<const void>> {};
    }
    auto mutex__=data_->mutex_;
    {
        std::unique_lock<std::recursive_mutex> _l(*(mutex__));
        return{ data_->efunction_,data_->efunction_data_ };
    }
}

}

/*在QApplication构造时运行*/
Q_COREAPP_STARTUP_FUNCTION(__construct)



