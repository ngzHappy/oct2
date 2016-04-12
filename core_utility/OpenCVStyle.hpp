#ifndef OPENCVSTYLE_HPP
#define OPENCVSTYLE_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

class OpenCVItem;
#include <QtWidgets/qproxystyle.h>
#include "core_utility_global.hpp"

class CORE_UTILITYSHARED_EXPORT OpenCVStyle : public QProxyStyle {
    Q_OBJECT
private:
    typedef QProxyStyle P;
public:
    explicit OpenCVStyle(QStyle * parent=nullptr);
    
MACRO_PROTECTED:
    virtual void drawComplexControl(ComplexControl control,const QStyleOptionComplex *option,QPainter *painter,const QWidget *widget=Q_NULLPTR) const override;
    virtual void drawControl(ControlElement element,const QStyleOption *option,QPainter *painter,const QWidget *widget=Q_NULLPTR) const override;
    virtual void drawItemPixmap(QPainter *painter,const QRect &rect,int alignment,const QPixmap &pixmap) const override;
    virtual void drawItemText(QPainter *painter,const QRect &rect,int flags,const QPalette &pal,bool enabled,const QString &text,QPalette::ColorRole textRole=QPalette::NoRole) const override;
    virtual void drawPrimitive(PrimitiveElement element,const QStyleOption *option,QPainter *painter,const QWidget *widget=Q_NULLPTR) const override;
    virtual QPixmap generatedIconPixmap(QIcon::Mode iconMode,const QPixmap &pixmap,const QStyleOption *opt) const override;
    virtual SubControl hitTestComplexControl(ComplexControl control,const QStyleOptionComplex *option,const QPoint &pos,const QWidget *widget=Q_NULLPTR) const override;
    virtual QRect itemPixmapRect(const QRect &r,int flags,const QPixmap &pixmap) const override;
    virtual QRect itemTextRect(const QFontMetrics &fm,const QRect &r,int flags,bool enabled,const QString &text) const override;
    virtual int layoutSpacing(QSizePolicy::ControlType control1,QSizePolicy::ControlType control2,Qt::Orientation orientation,const QStyleOption *option=Q_NULLPTR,const QWidget *widget=Q_NULLPTR) const override;
    virtual int pixelMetric(PixelMetric metric,const QStyleOption *option=Q_NULLPTR,const QWidget *widget=Q_NULLPTR) const override;
    virtual void polish(QWidget *widget) override;
    virtual void polish(QPalette &pal) override;
    virtual void polish(QApplication *app) override;
    virtual QSize sizeFromContents(ContentsType type,const QStyleOption *option,const QSize &size,const QWidget *widget) const override;
    virtual QIcon standardIcon(StandardPixmap standardIcon,const QStyleOption *option=Q_NULLPTR,const QWidget *widget=Q_NULLPTR) const override;
    virtual QPalette standardPalette() const override;
    virtual QPixmap standardPixmap(StandardPixmap standardPixmap,const QStyleOption *opt,const QWidget *widget=Q_NULLPTR) const override;
    virtual int styleHint(StyleHint hint,const QStyleOption *option=Q_NULLPTR,const QWidget *widget=Q_NULLPTR,QStyleHintReturn *returnData=Q_NULLPTR) const override;
    virtual QRect subControlRect(ComplexControl cc,const QStyleOptionComplex *option,SubControl sc,const QWidget *widget) const override;
    virtual QRect subElementRect(SubElement element,const QStyleOption *option,const QWidget *widget) const override;
    virtual void unpolish(QWidget *widget) override;
    virtual void unpolish(QApplication *app) override;
    virtual ~OpenCVStyle();
public:
    /*my defined*/
    const QColor & opencvWindowBackGroundColor()const;
    static OpenCVStyle * instance();
MACRO_PROTECTED:
    QColor setOpencvWindowBackGroundColor(const QColor &);
    friend class OpenCVItem;
};

#endif // OPENCVSTYLE_HPP
