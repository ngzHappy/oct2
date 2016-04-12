#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#include "../OpenCVChartImage.hpp"
#include "../OpenCVUtility.hpp"
#include <QtGui/qimage.h>
#include <private/qimage_p.h>
#include <QtWidgets/qfiledialog.h>
#include <cassert>
#include <QtCharts>
#include <QtCore/qdebug.h>
#include <QtWidgets/qgraphicsitem.h> 
#include <limits>

namespace {
namespace __private {

class Item :public QGraphicsPixmapItem {
public:

};

}
}

OpenCVChartImage::OpenCVChartImage(QGraphicsItem * _a_p)
    :P(_a_p) {
    item_chart_image_about_paint_=new __private::Item;
    item_chart_image_about_paint_->setParentItem(this);
    item_chart_image_about_paint_->setZValue(
        std::numeric_limits<float>::lowest());

    connect(this,&OpenCVChartImage::_sp_update_image_,
        this,&OpenCVChartImage::_p_update_image_,
        Qt::ConnectionType::QueuedConnection);

    connect(this,&OpenCVChartImage::_sp_update_image_pos,
        this,&OpenCVChartImage::_p_update_image_pos,
        Qt::ConnectionType::QueuedConnection);

}

void OpenCVChartImage::setGridLineVisible(const bool _a_xv,const bool _a_yv) {
    if (chart_==nullptr) { return; }
    if (chart_->axisX(series_)==nullptr) { return; }
    if (chart_->axisY(series_)==nullptr) { return; }
    chart_->axisX(series_)->setGridLineVisible(_a_xv);
    chart_->axisY(series_)->setGridLineVisible(_a_yv);
}

const QImage & OpenCVChartImage::getChartImage() const {
    return chart_image_;
}

QtCharts::QLineSeries * OpenCVChartImage::insertLine(
    QList<QPointF>&& _a_,
    bool _a_close
    ) {
    if (chart_==nullptr) { return nullptr; }
    if (series_==nullptr) { return nullptr; }
    if (_a_.isEmpty()) { return nullptr; }
    QtCharts::QLineSeries * _v_line=new QtCharts::QLineSeries;
    if (_a_close) { _a_.push_back(_a_.first()); }
    _v_line->append(_a_);
    chart_->addSeries(_v_line);
    chart_->setAxisX(chart_->axisX(series_),_v_line);
    chart_->setAxisY(chart_->axisY(series_),_v_line);
    _v_line->setPen(QPen(QColor(150,255,100,199),2.12));
    _v_line->setBrush(QColor(255,0,0));
    _v_line->setPointsVisible(true);
    return _v_line;
}

namespace {

constexpr double _value_max_() { return 260; }

QSizeF fit_size_(
    double width_,double height_,
    double dx_,double dy_
    ) {
    if (width_==height_) {
        /*长宽相等,缩放到最大值*/
        dx_=std::max({ dx_,dy_ ,_value_max_() });
        return QSizeF(dx_,dx_);
    }
    else {
        if (width_>height_) {
            /*宽大于高,按照高缩放*/
            dy_=std::max(_value_max_(),dy_);
            dx_=dy_/height_*width_;
            return QSizeF(dx_,dy_);
        }
        else {
            /*高大于宽,按照宽缩放*/
            dx_=std::max(_value_max_(),dx_);
            dy_=dx_/width_*height_;
            return QSizeF(dx_,dy_);
        }
    }

}

}

template<typename _t_CHARTIMAGE_t__>
void OpenCVChartImage::_p_setChartImage(_t_CHARTIMAGE_t__ &&_chartImage_) {
    chart_image_=std::forward<_t_CHARTIMAGE_t__>(_chartImage_);
    _p_private__set_image();
    const auto _v_width=chart_image_.width();
    const auto _v_height=chart_image_.height();
    if (_v_width<=0) { return; }
    if (_v_height<=0) { return; }

    chart_image_about_paint_=QPixmap::fromImage(chart_image_);

    {
        auto size_=this->minimumSize();
        size_=fit_size_(
            _v_width,_v_height,
            size_.width()*1.25,size_.height()*1.25);
        this->resize(size_);
    }

    {
        QList<QPointF> _v_d;
        _v_d.push_back(QPointF(0,0));
        _v_d.push_back(QPointF(0,_v_height));
        _v_d.push_back(QPointF(_v_width,_v_height));
        _v_d.push_back(QPointF(_v_width,0));
        setData(std::move(_v_d));
        series_->setPen(QPen(QColor(1,2,3,0),0));
    }
    assert(this->chart_);
    assert(this->layout_);
    assert(this->series_);
    this->chart_->axisX(this->series_)->setRange(0,_v_width);
    this->chart_->axisY(this->series_)->setRange(0,_v_height);
    this->chart_->axisY(this->series_)->setReverse(true);
    setColor(Qt::transparent);
    update();
}

void OpenCVChartImage::paint(
    QPainter *painter,
    const QStyleOptionGraphicsItem * a,
    QWidget * b) {

    const auto _v_width=chart_image_.width();
    const auto _v_height=chart_image_.height();

    if (_v_width<=0) { return; }
    if (_v_height<=0) { return; }

    QPointF top_left_=chart_->mapToPosition(
        QPointF(0,_v_height),this->series_);
    top_left_=chart_->mapToItem(this,top_left_);

    QPointF bottom_right_=chart_->mapToPosition(
        QPointF(_v_width,0),this->series_);
    bottom_right_=chart_->mapToItem(this,bottom_right_);

    //top_left_.setX(std::ceil(top_left_.x()));
    //top_left_.setY(std::ceil(top_left_.y()));
    //bottom_right_.setX(std::floor(bottom_right_.x()));
    //bottom_right_.setY(std::floor(bottom_right_.y()));

    QRectF target_rect_(top_left_,bottom_right_);

    {
        auto _v_size=chart_image_about_paint_.size();
        if ((_v_size.width()!=target_rect_.width())||
            (_v_size.height()!=target_rect_.height())
            ) {
            _v_size.setWidth(static_cast<int>(target_rect_.width()));
            _v_size.setHeight(static_cast<int>(target_rect_.height()));
            chart_image_about_paint_=
                QPixmap::fromImage(
                chart_image_.scaled(
                    _v_size,
                    Qt::AspectRatioMode::IgnoreAspectRatio,
                    Qt::TransformationMode::SmoothTransformation)
                    );
            _sp_update_image_({});
        }
    }

    if (item_chart_image_about_paint_->pos()!=top_left_) {
        _sp_update_image_pos(top_left_,{});
    }

    P::paint(painter,a,b);
   
}

void OpenCVChartImage::_p_update_image_pos(QPointF _top_left_) {
    item_chart_image_about_paint_->setPos(_top_left_);
}
void OpenCVChartImage::_p_update_image_() {
    item_chart_image_about_paint_->setPixmap(chart_image_about_paint_);
}

void OpenCVChartImage::saveImage() {
    return P::saveImage();
}

void OpenCVChartImage::renderTo(QImage & o){
    return P::renderTo(o);
}

void OpenCVChartImage::setChartImage(const QImage&_chartImage_) {
    _p_setChartImage(_chartImage_);
}

void OpenCVChartImage::setChartImage(QImage&&_chartImage_) {
    _p_setChartImage(std::move(_chartImage_));
}

OpenCVChartImage::~OpenCVChartImage() {

}

void OpenCVChartImage::_p_private__set_image() {
    {
        QImage & image_input_=chart_image_;
        QImageData * ptr_=image_input_.data_ptr();
        if ((ptr_)&&(ptr_->cleanupFunction)) {
            bool need_copy_=true;
            if (ptr_->cleanupFunction==OpenCVUtility::getHandleQImage()) {
                if (ptr_->cleanupInfo) {
                    cv::Mat * mat_=reinterpret_cast<cv::Mat *>(ptr_->cleanupInfo);
                    if (mat_->u) {
                        need_copy_=false;/*此处已经完成是否拷贝的决策*/
                        if (mat_->u->refcount!=1) {
                            image_input_=image_input_.copy();
                        }
                    }
                }
            }
            if (need_copy_) { image_input_=image_input_.copy(); }
        }
        else {
            image_input_.detach();/*获得独立备份*/
        }
    }
}
