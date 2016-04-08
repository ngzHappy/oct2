#ifndef OPENCVCHARTIMAGE_0_HPP
#define OPENCVCHARTIMAGE_0_HPP() 1

#include "OpenCVLineSeriesItem.hpp"
#include <QtGui/qpixmap.h>

class CORE_UTILITYSHARED_EXPORT OpenCVChartImage : public OpenCVLineSeriesItem
{
    Q_OBJECT
private:
    typedef OpenCVLineSeriesItem P;
    using P::setColor;
    using P::setCentrePointPaint;
    using P::setData;
MACRO_PROTECTED:
    QImage chart_image_;
    QPixmap chart_image_about_paint_;
public:
    explicit OpenCVChartImage(QGraphicsItem * /**/=nullptr);
    ~OpenCVChartImage();
public:
    void setChartImage(const QImage& /*chartImage*/);
    void setChartImage(QImage&& /*chartImage*/);
    const QImage & getChartImage() const;
    const QImage & chartImage() const{ return getChartImage();}
    QtCharts::QLineSeries * insertLine(QList<QPointF>&&,bool=false);
    template<typename B,typename E>
    QtCharts::QLineSeries * insertLine(B,E,bool=false);
    template<typename U>
    QtCharts::QLineSeries * insertLine(const std::initializer_list<U> &,bool=false);
private: 
    template<typename _t_CHARTIMAGE_t__>
    void _p_setChartImage(_t_CHARTIMAGE_t__ && /*chartImage*/);
    void _p_private__set_image();
protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
public:
    QtCharts::QLineSeries * insertLine(const QList<QPointF>& _a_,bool _close_=false) {
        QList<QPointF> _v_(_a_);
        return insertLine(std::move(_v_),_close_);
    }
};

template<typename B,typename E>
QtCharts::QLineSeries * OpenCVChartImage::insertLine(B b,E e,bool c) {
    QList<QPointF> _v_;
    for (;b!=e;++b) {
        _v_.push_back( QPointF(getX(b),getY(b)) );
    }
    return insertLine(std::move(_v_),c);
}

template<typename U>
QtCharts::QLineSeries * OpenCVChartImage::insertLine(const std::initializer_list<U> & a,bool c) {
    return insertLine(a.begin(),a.end(),c);
}

#endif // OPENCVCHARTIMAGE_HPP
