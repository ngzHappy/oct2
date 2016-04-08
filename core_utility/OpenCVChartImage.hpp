#ifndef OPENCVCHARTIMAGE_0_HPP
#define OPENCVCHARTIMAGE_0_HPP() 1

#include "OpenCVLineSeriesItem.hpp"

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
public:
    explicit OpenCVChartImage(QGraphicsItem * /**/=nullptr);
    ~OpenCVChartImage();
public:
    void setChartImage(const QImage& /*chartImage*/);
    void setChartImage(QImage&& /*chartImage*/);
    const QImage & getChartImage() const;
    const QImage & chartImage() const{ return getChartImage();}
private: 
    template<typename _t_CHARTIMAGE_t__>
    void _p_setChartImage(_t_CHARTIMAGE_t__ && /*chartImage*/);
    void _p_private__set_image();
protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
};

#endif // OPENCVCHARTIMAGE_HPP
