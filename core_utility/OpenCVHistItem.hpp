﻿#ifndef OPENCVHISTITEM_HPP
#define OPENCVHISTITEM_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include "OpenCVItem.hpp"
class QGraphicsLayout;
namespace QtCharts{
class QChart;
class QBarSeries;
class QBarSet;
}

class CORE_UTILITYSHARED_EXPORT OpenCVHistItem : public OpenCVItem {
    Q_OBJECT
MACRO_PROTECTED:
    typedef OpenCVItem P;
    QGraphicsLayout * layout_=nullptr;
    QtCharts::QChart * chart_=nullptr;
    QtCharts::QBarSeries * bar_series_=nullptr;
    QtCharts::QBarSet * bar_set_=nullptr;
    QColor color_;
    QList<qreal> data_;
public:
    OpenCVHistItem(QGraphicsItem * /**/=nullptr);
    ~OpenCVHistItem();

    QtCharts::QChart * getChart() const { return chart_; }

    void setColor(const QColor &);
    const QColor & getColor()const { return color_; }

    void setData(QList<qreal> &&);
    void setData(const QList<qreal> & d_) { QList<qreal> d=d_; setData(std::move(d)); }
    template<typename BI,typename EI>
    void setData(BI b,EI e);
    void renderTo(QImage &) override;
protected:
    void _init(QtCharts::QChart *);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
};

template<typename BI,typename EI>
void OpenCVHistItem::setData(BI b,EI e) {
    QList<qreal> d;
    for (; b!=e; ++b) { d.push_back(*b); }
    setData(std::move(d));
}

#endif // OPENCVHISTITEM_HPP
