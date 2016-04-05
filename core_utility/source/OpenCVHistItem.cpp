#include "OpenCVHistItem.hpp"
#include <QtWidgets/qgraphicslinearlayout.h>

OpenCVHistItem::OpenCVHistItem(QGraphicsItem * item_)
    :P(item_),
    color_(100,100,100,70) {
    this->resize(512,512);
    this->setMinimumWidth(256);
    this->setMinimumHeight(256);
}

OpenCVHistItem::~OpenCVHistItem() {

}

void OpenCVHistItem::renderTo(QImage & i) {
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

void OpenCVHistItem::_init(QtCharts::QChart *_chart_) {
    using namespace QtCharts;
    _chart_->setBackgroundBrush(Qt::transparent);
    _chart_->setAnimationOptions(QChart::SeriesAnimations);
    _chart_->legend()->hide();
    _chart_->setBackgroundVisible(false);

    QBarSet * _barset_=new QBarSet("?");
    _barset_->append(data_);
    _barset_->setBrush(color_);
    _barset_->setBorderColor(color_);

    QBarSeries * _bars_=new QBarSeries;
    _bars_->append(_barset_);
    _bars_->setBarWidth(1);

    _chart_->addSeries(_bars_);
    _chart_->createDefaultAxes();

    _chart_->axisX()->setGridLineVisible(false);
    _chart_->axisX()->setLabelsVisible(false);
    _chart_->axisX()->setLineVisible(false);

    bar_set_=_barset_;
    bar_series_=_bars_;

}

void OpenCVHistItem::paint(
    QPainter * painter,
    const QStyleOptionGraphicsItem * option,
    QWidget * widget) {
    return P::paint(painter,option,widget);
}

void OpenCVHistItem::setColor(const QColor &c) {
    if (c==color_) { return; }
    color_=c;
    if (bar_set_) {
        bar_set_->setBrush(color_);
        bar_set_->setBorderColor(color_);
    }
}

void OpenCVHistItem::setData(QList<qreal> && data__) {
    QGraphicsLinearLayout * _layout_=new QGraphicsLinearLayout;
    {
        data_=std::move(data__);
        layout_=_layout_;
        this->setLayout(layout_);/*this function will delete old layout*/
        _layout_->setSpacing(0);
        chart_=nullptr;
        bar_series_=nullptr;
        bar_set_=nullptr;
    }
    if (data_.isEmpty()) { return; }
    {
        using namespace QtCharts;
        chart_=new QChart;
        _layout_->addItem(chart_);
    }
    _init(chart_);
}

