/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include <QtCore/qdir.h>
#include <list>
//#include <QtCharts>

#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qerrormessage.h>
#include <QtCore/qdebug.h>
namespace {
int ErrorCallback(
    int status/*cv::Error::Code*/,
    const char* func_name,
    const char* err_msg,
    const char* file_name,
    int line,
    void* /*userdata*/) {
    QString __error_;

#if !defined(NDEBUG)
    cv::Error::Code estatus= static_cast<cv::Error::Code>(status);
    (void)estatus;
#endif

    {
        QTextStream stream_(&__error_);
        stream_
            <<"function name:"<<func_name<<endl
            <<"error message:"<<err_msg<<endl
            <<"file name:"<<file_name<<endl
            <<"line:"<<line;
        stream_.flush();
    }

    if (qApp) {
        qDebug().noquote()<<__error_;
        QErrorMessage errorBox;
        errorBox.showMessage(__error_);
        errorBox.exec();
    }
    else {
        qDebug().noquote()<<__error_;
    }

    return 0;
    (void)status;
}
}
/*当qapplication运行时注册此函数*/
static void _set_opencv_error_on_qt_start_up() {
    cv::redirectError(&ErrorCallback);
}
Q_COREAPP_STARTUP_FUNCTION(_set_opencv_error_on_qt_start_up)

namespace {
inline constexpr int image_width() { return 512; }
inline constexpr int image_height() { return 512; }
inline constexpr int rect_width() { return 100; }
inline constexpr int rect_height() { return 60; }
inline constexpr double deg_to_rad(double _v_) { return _v_/180*3.141592654; }
QImage getTestImage(double angle/*deg*/) {
    QImage image_(image_width(),image_height(),QImage::Format_RGB32);
    image_.fill(QColor(0,0,0));
    QPainter painter_(&image_);
    painter_.translate(image_width()/2,image_height()/2);
    painter_.rotate(angle);
    painter_.setPen(QPen(QColor(255,255,255),1));
    painter_.setBrush(QColor(255,255,255));
    painter_.drawRect(QRectF(
        (-rect_width())/2,
        (-rect_height())/2,
        rect_width(),
        rect_height()
        ));
    return image_.convertToFormat(QImage::Format_Grayscale8);
}

}

namespace { 

class FreeManPoint {
protected:
    std::int32_t x_;
    std::int32_t y_;
    unsigned char code_/*0,1,2,3,4,5,6,7*/;
public:
    FreeManPoint() :x_(-1),y_(-1),code_(8){}
    FreeManPoint(std::int32_t _x_,std::int32_t _y_,unsigned char _c_) :
        x_(_x_),y_(_y_),code_(_c_){}
    FreeManPoint(std::int32_t _x_,std::int32_t _y_,char _c_) :
        x_(_x_),y_(_y_),code_(static_cast<unsigned char>(_c_)){}
public:
    void setX(const std::int32_t& /*x*/);
    void setX(std::int32_t&& /*x*/);
    const std::int32_t & getX() const;
    const std::int32_t & x() const{ return getX();}
    void setY(const std::int32_t& /*y*/);
    void setY(std::int32_t&& /*y*/);
    const std::int32_t & getY() const;
    const std::int32_t & y() const{ return getY();}
    void setCode(const unsigned char& /*code*/);
    void setCode(unsigned char&& /*code*/);
    const short getCode() const;
    const short code() const{ return getCode();}
private: 
    template<typename _t_CODE_t__>void _p_setCode(_t_CODE_t__ && /*code*/);
    template<typename _t_X_t__>void _p_setX(_t_X_t__ && /*x*/);
    template<typename _t_Y_t__>void _p_setY(_t_Y_t__ && /*y*/);
};

const std::int32_t & FreeManPoint::getY() const{return y_;}
template<typename _t_Y_t__>
void FreeManPoint::_p_setY(_t_Y_t__ &&_y_){
    y_=std::forward<_t_Y_t__>(_y_);
}
void FreeManPoint::setY(const std::int32_t&_y_){_p_setY(_y_);}
void FreeManPoint::setY(std::int32_t&&_y_){ _p_setY(std::move(_y_));}
const short FreeManPoint::getCode() const{return code_;}
template<typename _t_CODE_t__>
void FreeManPoint::_p_setCode(_t_CODE_t__ &&_code_) {
    code_=std::forward<_t_CODE_t__>(_code_);
}
void FreeManPoint::setCode(const unsigned char&_code_){
    _p_setCode(_code_);
}
void FreeManPoint::setCode(unsigned char&&_code_){
    _p_setCode(std::move(_code_));
}
const std::int32_t & FreeManPoint::getX() const{return x_;}
template<typename _t_X_t__>
void FreeManPoint::_p_setX(_t_X_t__ &&_x_){
    x_=std::forward<_t_X_t__>(_x_);
}
void FreeManPoint::setX(const std::int32_t&_x_){_p_setX(_x_);}
void FreeManPoint::setX(std::int32_t&&_x_){_p_setX(std::move(_x_));}

std::list<std::vector<FreeManPoint>> 
findContoursFreeman(cv::Mat input_image) noexcept(false/*cv::Exception*/){
    typedef void(*FreeCvMemStorageType)(CvMemStorage*);
    
    CvChain* chain=nullptr;
    CvMemStorage* storage=nullptr;
    storage=cvCreateMemStorage(0)/*default*/;

    if (storage==nullptr) { return{}; }

    const std::unique_ptr<CvMemStorage,FreeCvMemStorageType> _storage_lock
        (storage,[](CvMemStorage* data_) {
        cvClearMemStorage(data_)/*清空数据*/;
        cvReleaseMemStorage(&data_)/*释放内存*/;
    });
     
    cvFindContours(
        &IplImage(input_image),
        storage, 
        (CvSeq**)(&chain), 
        sizeof(*chain), 
        CV_RETR_EXTERNAL, CV_CHAIN_CODE );

    /*结果*/
    std::list<std::vector<FreeManPoint>> _ans_;
    
    for(;chain!=nullptr;chain=(CvChain*)chain ->h_next) {   
        
        CvSeqReader reader; 
        int i=0;
        int total=chain->total;
        cvStartReadSeq((CvSeq*)chain,&reader,0); 

        CvChainPtReader reader_point;
        cvStartReadChainPoints((CvChain*)chain, &reader_point);

        std::vector<FreeManPoint> _v_points;
        _v_points.reserve(total);

        for(i=0;i<total;i++) 
        { 
            char code/*链码*/; 
            CV_READ_SEQ_ELEM(code, reader); 

            CvPoint pt/*点*/;
            CV_READ_CHAIN_POINT(pt,reader_point);

            _v_points.emplace_back(pt.x,pt.y,code);
        }
        _ans_.push_back(std::move(_v_points));
    }
    return std::move(_ans_);

} 

}

extern void run(OpenCVWindow *) try{
   
    {
        QDir dir_(qApp->applicationDirPath());
        dir_.mkdir(APP_NAME_);
    }

    const QString fileName_=qApp->applicationDirPath()
        +("/"/**/APP_NAME_)
        +"/ans.txt";
    QFile file_(fileName_);
    file_.open(QIODevice::WriteOnly|QIODevice::Text);
    
    QTextStream stream_(&file_);

    for (int deg=0; deg<360;++deg) {
        /*生成测试图片*/
        QImage image_=getTestImage(deg);
        /*将QImage 转换为 cv::Mat*/
        cv::Mat input_image=OpenCVUtility::tryRead(image_.copy());
        
        std::list<std::vector<FreeManPoint>> ans_=
        findContoursFreeman(input_image);
      
        std::int32_t count_[8]{0,0,0,0,0,0,0,0};
        for (const auto &i:ans_) {
            for (const auto & j:i) {
                ++count_[j.code()];
            }
        }

        const double weight_=
            count_[0]+count_[1]+count_[2]+count_[3]+
            count_[4]+count_[5]+count_[6]+count_[7];
        double diff_=(
            std::abs(count_[0]-count_[4])+
            std::abs(count_[1]-count_[5])+
            std::abs(count_[2]-count_[6])+
            std::abs(count_[3]-count_[7])
            )/weight_;
        /*输出到控制台*/
        //std::cout<<count_[0]<<",";
        //std::cout<<count_[1]<<",";
        //std::cout<<count_[2]<<",";
        //std::cout<<count_[3]<<",";
        //std::cout<<count_[4]<<",";
        //std::cout<<count_[5]<<",";
        //std::cout<<count_[6]<<",";
        //std::cout<<count_[7]<<",";
        //std::cout<<std::endl;
        /*输出到文件*/
        stream_<<count_[0]<<",";
        stream_<<count_[1]<<",";
        stream_<<count_[2]<<",";
        stream_<<count_[3]<<",";
        stream_<<count_[4]<<",";
        stream_<<count_[5]<<",";
        stream_<<count_[6]<<",";
        stream_<<count_[7]<<",";
        stream_<<weight_<<",";
        stream_<<diff_<<",";
        stream_<<endl;
        
        std::cout<<deg<<","<<diff_<<std::endl;

    }

    qDebug().noquote()<<"out filename:"<<QDir::cleanPath(fileName_);

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

//http://stackoverflow.com/questions/22326412/how-to-get-the-freeman-chain-code-in-opencv
//http://blog.csdn.net/xinfeng2005/article/details/8123662
