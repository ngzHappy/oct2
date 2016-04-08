#ifndef OPENCVSCATTERITEM_HPP__LINE0x00
#define OPENCVSCATTERITEM_HPP__LINE0x00() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include "OpenCVItem.hpp"
#include <QtCore/qlist.h>
#include <QtCharts>

class CORE_UTILITYSHARED_EXPORT OpenCVLineSeriesItem : public OpenCVItem {
    Q_OBJECT
private:
    typedef OpenCVItem P;
    static void _OpenCVLineSeriesItem_init( OpenCVLineSeriesItem * );
MACRO_PROTECTED:
    QList<QPointF> data_;
    QGraphicsLinearLayout * layout_=nullptr;
    QtCharts::QChart * chart_=nullptr;
    QtCharts::QLineSeries * series_=nullptr;
    QColor color_;
    QPointF cen_point_;/*中心点 value*/
    std::shared_ptr< std::function<void(QPainter *)> > cen_paint_;
public:
    OpenCVLineSeriesItem(QGraphicsItem *parent=nullptr);
    ~OpenCVLineSeriesItem();

    void renderTo(QImage &) override;
    QtCharts::QChart * getChart() const { return chart_; }
    QtCharts::QLineSeries * getLineSeries() const { return series_; }
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
    void resizeEvent(QGraphicsSceneResizeEvent *event)override;
};

#endif // OPENCVSCATTERITEM_HPP
