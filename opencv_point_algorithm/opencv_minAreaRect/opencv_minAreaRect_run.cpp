/*run.cpp*/
#include <QtCharts>
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <vector>
#include <array>
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
            <<"function name:"<<func_name
            <<"error message:"<<err_msg
            <<"file name:"<<file_name
            <<"line:"<<line;
    }

    if (qApp) {
        QErrorMessage errorBox;
        errorBox.showMessage(__error_,"error");
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

static inline std::vector<cv::Point2f>
genRandPoint() {
    enum {SIZE=100};
    std::vector<cv::Point2f> ans;
    ans.reserve(SIZE);
    for (std::intptr_t i=0; i<SIZE;++i) {
        const double x_=std::sin(double(std::rand()))*0.707;
        const double y_=std::cos(double(std::rand()))*0.707;
        ans.emplace_back( 
            static_cast<float>(x_+y_),
            static_cast<float>(x_-y_));
    }
    return std::move(ans);
}

extern void run(OpenCVWindow * window) try{

    std::vector<cv::Point2f> points_input=
        genRandPoint();

    auto * item_ = window->insertScatter(points_input.begin(),points_input.end());
    item_->setWindowTitle(u8"外接矩形"_qs);

    cv::RotatedRect rect = cv::minAreaRect( points_input );
    std::cout<<rect.center<<std::endl;
    std::cout<<rect.angle<<std::endl;
    std::cout<<rect.size<<std::endl;
    std::array<cv::Point2f,4> points_;
    rect.points( &points_[0] );
    std::cout
        <<points_[0]<<std::endl
        <<points_[1]<<std::endl
        <<points_[2]<<std::endl
        <<points_[3]<<std::endl;

    /*绘制外接矩形*/
    QtCharts::QLineSeries * series_=new QtCharts::QLineSeries;
    series_->append({points_[0].x,points_[0].y});
    series_->append({points_[1].x,points_[1].y});
    series_->append({points_[2].x,points_[2].y});
    series_->append({points_[3].x,points_[3].y});
    series_->append({points_[0].x,points_[0].y});
    series_->setPen(QPen(QColor(0,0,0),2));
    series_->setPointsVisible(true);
    auto * chart_=item_->getChart();
    chart_->addSeries(series_);
    chart_->setAxisX(chart_->axisX(item_->getScatterSeries()),series_);
    chart_->setAxisY(chart_->axisY(item_->getScatterSeries()),series_);
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}
