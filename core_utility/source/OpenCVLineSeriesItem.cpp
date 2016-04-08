#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#include "OpenCVLineSeriesItem.hpp"
#include <memory>

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

void OpenCVLineSeriesItem::_OpenCVLineSeriesItem_init(OpenCVLineSeriesItem * this_) {
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
    __private::Range range_(this_->data_);
    this_->chart_->axisX()->setRange(range_.minX,range_.maxX);
    this_->chart_->axisY()->setRange(range_.minY,range_.maxY);
    this_->cen_point_=range_.centrePoint;
    /*设置颜色*/
    this_->setColor(this_->color());
    /*显示点*/
    this_->series_->setPointsVisible(true);
}



void OpenCVLineSeriesItem::renderTo(QImage & i) {
    if (chart_) {

        QSizeF csize_=chart_->size();
        i=QImage(
            qRound(csize_.width()+0.51),qRound(csize_.height()+0.51),
            QImage::Format_RGBA8888
            );
        i.fill(QColor(0,0,0,0));

        QGraphicsScene * sc_=chart_->scene();
        if (sc_==nullptr) { return; }
        sc_->setActiveWindow(this);

        QPointF spos_=chart_->mapToScene(chart_->rect().topLeft());

        QPainter painter(&i);
        sc_->render(
            &painter,
            QRectF(0,0,i.width(),i.height()),
            QRectF(spos_.x(),spos_.y(),i.width(),i.height())
            );

    }
}

OpenCVLineSeriesItem::OpenCVLineSeriesItem(QGraphicsItem *parent)
    :P(parent) {
    color_=QColor(123,123,123,200);
    cen_point_=QPointF(0,0);
    this->resize(512,512);
    this->setMinimumWidth(256);
    this->setMinimumHeight(256);
}

void OpenCVLineSeriesItem::resizeEvent(QGraphicsSceneResizeEvent *event) {
    P::resizeEvent(event);
    if (chart_==nullptr) { return; }
    if (chart_->animationOptions()) {
        QTimer::singleShot(1998,this,[this]() {update(); });
        QTimer::singleShot(998,this,[this]() {update(); });
        QTimer::singleShot(500,this,[this]() {update(); });
        QTimer::singleShot(300,this,[this]() {update(); });
        QTimer::singleShot(200,this,[this]() {update(); });
        QTimer::singleShot(150,this,[this]() {update(); });
        QTimer::singleShot(100,this,[this]() {update(); });
        QTimer::singleShot(50,this,[this]() {update(); });
        QTimer::singleShot(30,this,[this]() {update(); });
    }
    else {
        QTimer::singleShot(1500,this,[this]() {update(); });
    }
}

OpenCVLineSeriesItem::~OpenCVLineSeriesItem() {

}


const QList<QPointF> & OpenCVLineSeriesItem::getData() const {
    return this->data_;
}

template<typename _t_DATA__t__>
void OpenCVLineSeriesItem::_p_setData(_t_DATA__t__ &&_data__) {
    layout_=new QGraphicsLinearLayout;
    data_=std::forward<_t_DATA__t__>(_data__);
    {
        layout_->setSpacing(0);
        this->setLayout(layout_);
    }
    _OpenCVLineSeriesItem_init(this);
}

void OpenCVLineSeriesItem::setData(const QList<QPointF>&_data__) {
    _p_setData(_data__);
}

void OpenCVLineSeriesItem::setData(QList<QPointF>&&_data__) {
    _p_setData(std::move(_data__));
}


const QColor & OpenCVLineSeriesItem::getColor() const {
    return color_;
}

template<typename _t_COLOR_t__>
void OpenCVLineSeriesItem::_p_setColor(_t_COLOR_t__ &&_color_) {
    color_=std::forward<_t_COLOR_t__>(_color_);
    if (series_) {
        series_->setBrush(color_);
        series_->setColor(color_);
        series_->setPen(QPen(QColor(color_),2));
    }
}

void OpenCVLineSeriesItem::paint(
    QPainter *painter,
    const QStyleOptionGraphicsItem *option,
    QWidget *widget) {
    P::paint(painter,option,widget);
    {
        painter->setRenderHint(QPainter::HighQualityAntialiasing,true);
    }
    if (chart_ && series_) {
        if (cen_paint_&&(*cen_paint_)) {
            QPointF cen_position_=chart_->mapToPosition(cen_point_,series_);
            QPointF d_cen_position_=chart_->mapToPosition(cen_point_+QPointF{ 0.5,0.5 },series_);
            d_cen_position_-=cen_position_;
            cen_position_=chart_->mapToItem(this,cen_position_);
            painter->save();
            painter->translate(cen_position_);
            const auto len_=std::sqrt(
                d_cen_position_.x()*d_cen_position_.x()+
                d_cen_position_.y()*d_cen_position_.y()
                )/1.50;
            painter->scale(std::abs(d_cen_position_.x()/len_),std::abs(d_cen_position_.y()/len_));
            (*cen_paint_)(painter);
            painter->restore();
        }
    }
}

const std::shared_ptr< std::function<void(QPainter *)> > & OpenCVLineSeriesItem::getCentrePointPaint() const {
    return cen_paint_;
}

template<typename _t_CENTREPOINTPAINT_t__>
void OpenCVLineSeriesItem::_p_setCentrePointPaint(_t_CENTREPOINTPAINT_t__ &&_centrePointPaint_) {
    if (cen_paint_==_centrePointPaint_) { return; }
    cen_paint_=std::forward<_t_CENTREPOINTPAINT_t__>(_centrePointPaint_);
    this->update();
}

void OpenCVLineSeriesItem::setCentrePointPaint(const std::shared_ptr< std::function<void(QPainter *)> >&_centrePointPaint_) {
    _p_setCentrePointPaint(_centrePointPaint_);
}

void OpenCVLineSeriesItem::setCentrePointPaint(std::shared_ptr< std::function<void(QPainter *)> >&&_centrePointPaint_) {
    _p_setCentrePointPaint(std::move(_centrePointPaint_));
}


void OpenCVLineSeriesItem::setColor(const QColor&_color_) {
    _p_setColor(_color_);
}

void OpenCVLineSeriesItem::setColor(QColor&&_color_) {
    _p_setColor(std::move(_color_));
}

