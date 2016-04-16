#ifndef OPENCVVERTICALITEMS_HPP
#define OPENCVVERTICALITEMS_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include "OpenCVItem.hpp"
class QWidget;
class QGraphicsItem;
class QGraphicsLinearLayout;
class QGraphicsLayoutItem;

class CORE_UTILITYSHARED_EXPORT OpenCVVerticalItems : public OpenCVItem
{
    Q_OBJECT
    typedef OpenCVItem P;
MACRO_PROTECTED:
    QGraphicsLinearLayout*layout_=nullptr;
public:
    explicit OpenCVVerticalItems(QGraphicsItem * /*parent*/=nullptr);
    virtual ~OpenCVVerticalItems();

    virtual QGraphicsProxyWidget *addWidget(QWidget *,bool fixedHeight=false,QSize fixedMinSize=QSize(-1,-1));
    virtual void addItem(QGraphicsLayoutItem *p);

    void renderTo(QImage &)override;
public:
    void onXChanged()override;
    void onYChanged()override;
};

#endif // OPENCVVERTICALITEMS_HPP
