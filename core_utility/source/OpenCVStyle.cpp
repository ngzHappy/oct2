#include "OpenCvStyle.hpp"

OpenCVStyle::OpenCVStyle(QStyle * parent)
    :P(parent) {

}

OpenCVStyle::~OpenCVStyle() {

}

void OpenCVStyle::drawComplexControl(
        ComplexControl control,
        const QStyleOptionComplex *option,
        QPainter *painter,
        const QWidget *widget) const {
    return P::drawComplexControl(control,option,painter,widget);
}

void OpenCVStyle::drawControl(
    ControlElement element,
    const QStyleOption *option,
    QPainter *painter,const QWidget *widget) const {
    return P::drawControl(element,option,painter,widget);
}

void OpenCVStyle::drawItemPixmap(
    QPainter *painter,
    const QRect &rect,
    int alignment,
    const QPixmap &pixmap) const {
    return P::drawItemPixmap(painter,rect,alignment,pixmap);
}

void OpenCVStyle::drawItemText(
    QPainter *painter,
    const QRect &rect,
    int flags,
    const QPalette &pal,
    bool enabled,
    const QString &text,
    QPalette::ColorRole textRole) const {
    return P::drawItemText(painter,rect,flags,pal,enabled,text,textRole);
}

void OpenCVStyle::drawPrimitive(
    PrimitiveElement element,
    const QStyleOption *option,
    QPainter *painter,
    const QWidget *widget) const {
    return P::drawPrimitive(element,option,painter,widget);
}

QPixmap OpenCVStyle::generatedIconPixmap(
    QIcon::Mode iconMode,
    const QPixmap &pixmap,
    const QStyleOption *opt) const {
    return P::generatedIconPixmap(iconMode,pixmap,opt);
}

OpenCVStyle::SubControl OpenCVStyle::hitTestComplexControl(
    ComplexControl control,
    const QStyleOptionComplex *option,
    const QPoint &pos,
    const QWidget *widget) const {
    return P::hitTestComplexControl(control,option,pos,widget);
}

QRect OpenCVStyle::itemPixmapRect(
    const QRect &r,
    int flags,
    const QPixmap &pixmap) const {
    return P::itemPixmapRect(r,flags,pixmap);
}

QRect OpenCVStyle::itemTextRect(
    const QFontMetrics &fm,
    const QRect &r,
    int flags,
    bool enabled,
    const QString &text) const {
    return P::itemTextRect(fm,r,flags,enabled,text);
}

int OpenCVStyle::layoutSpacing(
    QSizePolicy::ControlType control1,
    QSizePolicy::ControlType control2,
    Qt::Orientation orientation,
    const QStyleOption *option,
    const QWidget *widget) const {
    return P::layoutSpacing(control1,control2,orientation,option,widget);
}

int OpenCVStyle::pixelMetric(
    PixelMetric metric,
    const QStyleOption *option,
    const QWidget *widget) const {
    return P::pixelMetric(metric,option,widget);
}

void OpenCVStyle::polish(QWidget *widget) {
    return P::polish(widget);
}
void OpenCVStyle::polish(QPalette &pal) {
    return P::polish(pal);
}
void OpenCVStyle::polish(QApplication *app) {
    return P::polish(app);
}
QSize OpenCVStyle::sizeFromContents(
    ContentsType type,
    const QStyleOption *option,
    const QSize &size,
    const QWidget *widget) const {
    return P::sizeFromContents(type,option,size,widget);
}

QIcon OpenCVStyle::standardIcon(
    StandardPixmap standardIcon,
    const QStyleOption *option,
    const QWidget *widget) const {
    return P::standardIcon(standardIcon,option,widget);
}

QPalette OpenCVStyle::standardPalette() const {
    return P::standardPalette();
}

QPixmap OpenCVStyle::standardPixmap(
    StandardPixmap standardPixmap,
    const QStyleOption *opt,
    const QWidget *widget) const {
    return P::standardPixmap(standardPixmap,opt,widget);
}

int OpenCVStyle::styleHint(
    StyleHint hint,
    const QStyleOption *option,
    const QWidget *widget,
    QStyleHintReturn *returnData) const {
    return P::styleHint(hint,option,widget,returnData);
}

QRect OpenCVStyle::subControlRect(
    ComplexControl cc,
    const QStyleOptionComplex *option,
    SubControl sc,
    const QWidget *widget) const {
    return P::subControlRect(cc,option,sc,widget);
}

QRect OpenCVStyle::subElementRect(
    SubElement element,
    const QStyleOption *option,
    const QWidget *widget) const {
    return P::subElementRect(element,option,widget);
}

void OpenCVStyle::unpolish(QWidget *widget) {
    return P::unpolish(widget);
}

void OpenCVStyle::unpolish(QApplication *app) {
    return P::unpolish(app);
}

