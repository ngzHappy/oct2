#ifndef OPENCVSCATTERITEM_HPP
#define OPENCVSCATTERITEM_HPP() 1

#include "OpenCVItem.hpp"
#include <QtCore/qlist.h>
#include <QtCharts>

class CORE_UTILITYSHARED_EXPORT OpenCVScatterItem : public OpenCVItem {
    Q_OBJECT
private:
    typedef OpenCVItem P;
MACRO_PROTECTED:
    QList<QPointF> data_;
    QGraphicsLinearLayout * layout_=nullptr;
    QtCharts::QChart * chart_=nullptr;
    QtCharts::QScatterSeries * series_=nullptr;
    QColor color_;
    QPointF cen_point_;/*中心点 value*/
    std::shared_ptr< std::function<void(QPainter *)> > cen_paint_;
public:
    OpenCVScatterItem(QGraphicsItem *parent=nullptr);
    ~OpenCVScatterItem();

    void renderTo(QImage &) override;
    QtCharts::QScatterSeries * getScatterSeries()const { return series_; }
public:
    void setData(const QList<QPointF>& /*data*/);
    void setData(QList<QPointF>&& /*data*/);
    const QList<QPointF> & getData() const;
    const QList<QPointF> & data() const { return getData(); }
private: template<typename _t_DATA_t__>
    void _p_setData(_t_DATA_t__ && /*data*/);
public:
    void setColor(const QColor& /*color*/);
    void setColor(QColor&& /*color*/);
    const QColor & getColor() const;
    const QColor & color() const { return getColor(); }
private: template<typename _t_COLOR_t__>
    void _p_setColor(_t_COLOR_t__ && /*color*/);
public:
    void setCentrePointPaint(const std::shared_ptr< std::function<void(QPainter *)> >& /*centrePointPaint*/);
    void setCentrePointPaint(std::shared_ptr< std::function<void(QPainter *)> >&& /*centrePointPaint*/);
    const std::shared_ptr< std::function<void(QPainter *)> > & getCentrePointPaint() const;
    const std::shared_ptr< std::function<void(QPainter *)> > & centrePointPaint() const { return getCentrePointPaint(); }
private: template<typename _t_CENTREPOINTPAINT_t__>
    void _p_setCentrePointPaint(_t_CENTREPOINTPAINT_t__ && /*centrePointPaint*/);
protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
};

#endif // OPENCVSCATTERITEM_HPP
