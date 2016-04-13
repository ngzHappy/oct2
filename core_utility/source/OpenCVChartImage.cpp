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

class Range {
public:
    double minX=-3; double minY=3;
    double maxX=-3; double maxY=3;
    QPointF centrePoint;
    Range(const QList<QPointF> & data_) { init(data_); }
private:
    void init(const QList<QPointF> & data_) {
        if (data_.size()==0) { return; }
        centrePoint=QPointF(0,0);
        intptr_t count_=0;
        minX=data_.first().x(); maxX=minX;
        minY=data_.first().y(); maxY=minY;
        auto pos=data_.begin();
        auto end=data_.end();
        for (; pos!=end; ++pos) {
            ++count_; centrePoint+=(*pos);
            if (minX>pos->x()) { minX=pos->x(); }
            if (maxX<pos->x()) { maxX=pos->x(); }
            if (minY>pos->y()) { minY=pos->y(); }
            if (maxY<pos->y()) { maxY=pos->y(); }
        }
        centrePoint/=count_;
        double lenx=std::abs(maxX-minX);
        double leny=std::abs(maxY-minY);
        lenx/=20; leny/=20;
        lenx=std::max(lenx,0.25);
        leny=std::max(leny,0.25);
        minX-=lenx; maxX+=lenx;
        minY-=leny; maxY+=leny;
    }
};

}
}

namespace {
namespace __private {

class Item :public QGraphicsPixmapItem {
public:

};

}
}

OpenCVChartImage::OpenCVChartImage(QGraphicsItem * _a_p)
    :P(_a_p) {
    connect(this,&OpenCVChartImage::_sp_update_image_,
        this,&OpenCVChartImage::_p_update_image_,
        Qt::ConnectionType::QueuedConnection);

    connect(this,&OpenCVChartImage::_sp_update_image_pos,
        this,&OpenCVChartImage::_p_update_image_pos,
        Qt::ConnectionType::QueuedConnection);

    connect(this,&OpenCVChartImage::_sp_update_later,
        this,&OpenCVChartImage::_p_update_later,
        Qt::ConnectionType::DirectConnection);
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
    _v_line->setPointsVisible(false);
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

static void __private__set__data(
    QList<QPointF> _data,
    OpenCVLineSeriesItem * this_
    ) {
        {
            this_->data_=std::move(_data);
            this_->layout_=new QGraphicsLinearLayout;
            {
                this_->layout_->setSpacing(0);
                this_->setLayout(this_->layout_);
            }
        }
        {
            if (this_->data_.size()<=0) {
                this_->chart_=nullptr;
                this_->series_=nullptr;
                this_->cen_point_=QPointF(0,0);
                return;
            }
            /*设置数据*/
            this_->series_=new QtCharts::QLineSeries;
            this_->chart_=new QtCharts::QChart;
            this_->series_->append(this_->data_);
            this_->chart_->addSeries(this_->series_);
            this_->layout_->addItem(this_->chart_);
            /*设置样式*/
            this_->chart_->setBackgroundBrush(Qt::transparent);
            this_->chart_->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
            this_->chart_->legend()->hide();
            this_->chart_->setBackgroundVisible(false);
            /*设置坐标系*/
            this_->chart_->createDefaultAxes();
            this_->chart_->axisY()->setReverse(true);
            __private::Range range_(this_->data_);
            this_->cen_point_=range_.centrePoint;
            /*设置颜色*/
            this_->setColor(this_->color());
            /*显示点*/
            this_->series_->setPointsVisible(false);
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
        __private__set__data(std::move(_v_d),this);
        series_->setPen(QPen(QColor(1,2,3,0),0));
    }

    assert(this->chart_);
    assert(this->layout_);
    assert(this->series_);

    /*there is a bug???*/
    this->chart_->axisY(this->series_)->setReverse(true);
    this->chart_->axisX(this->series_)->setRange(0,_v_width);
    this->chart_->axisY(this->series_)->setRange(0,_v_height);

    item_chart_image_about_paint_=new __private::Item;
    item_chart_image_about_paint_->setParentItem(chart_);
    item_chart_image_about_paint_->setZValue(
        std::numeric_limits<float>::lowest());

    update();
}

void OpenCVChartImage::mouseMoveEvent(
    QGraphicsSceneMouseEvent *event) {
    return P::mouseMoveEvent(event);
}

void OpenCVChartImage::_p_update_later() {
    if (chart_) { 
        chart_->update(chart_->plotArea());
    }
}

void OpenCVChartImage::paint(
    QPainter *painter,
    const QStyleOptionGraphicsItem * a,
    QWidget * b) {

    if (series_==nullptr) { return QGraphicsWidget::paint(painter,a,b); }
    if (chart_==nullptr) { return QGraphicsWidget::paint(painter,a,b); }

    const auto _v_width=chart_image_.width();
    const auto _v_height=chart_image_.height();

    if (_v_width<=0) { return; }
    if (_v_height<=0) { return; }

    QPointF top_left_=chart_->mapToPosition(
        QPointF(0,_v_height),this->series_);

    QPointF bottom_right_=chart_->mapToPosition(
        QPointF(_v_width,0),this->series_);

    QRectF target_rect_(top_left_,bottom_right_);

    {
        auto _v_size=chart_image_about_paint_.size();
        auto twidth=qRound(target_rect_.width());
        auto theight=qRound(target_rect_.height());

        if ((_v_size.width()!=twidth)||
            (_v_size.height()!=theight)
            ) {
            _v_size.setWidth(twidth);
            _v_size.setHeight(theight);
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

#if 0
    static auto test_draw_count_=0;
    qDebug()<<test_draw_count_++;
#endif
    /*painting bug?? on mouse move??*/
    if (chart_&&chart_->isUnderMouse()) {
        if ((cursor_pos_on_draw_==cursor().pos())&&
            (draw_updata_count_>1)) { return; }
        _sp_update_later({});
        ++draw_updata_count_;
        cursor_pos_on_draw_=cursor().pos();
    }
    else {
        draw_updata_count_=0;
        cursor_pos_on_draw_.setX(std::numeric_limits<int>::lowest());
        cursor_pos_on_draw_.setY((std::numeric_limits<int>::max)());
    }

}

void OpenCVChartImage::_p_update_image_pos(QPointF _top_left_) {
    if (chart_) {
        item_chart_image_about_paint_->setPos(_top_left_);
        chart_->update();
    }
}

void OpenCVChartImage::_p_update_image_() {
    if (chart_) {
        item_chart_image_about_paint_->setPixmap(chart_image_about_paint_);
        chart_->update();
    }
}

void OpenCVChartImage::saveImage() {
    return P::saveImage();
}

void OpenCVChartImage::renderTo(QImage & o) {
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
