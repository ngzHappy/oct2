﻿#ifndef OPENCVITEM_HPP
#define OPENCVITEM_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include <QtWidgets/qgraphicsitem.h>
#include <QtWidgets/qgraphicswidget.h>
#include <QtCore/qpointer.h>
#include "core_utility_global.hpp"

class CORE_UTILITYSHARED_EXPORT OpenCVItem : public QGraphicsWidget {
    Q_OBJECT
private:
    typedef QGraphicsWidget P;
public:

    explicit OpenCVItem(QGraphicsItem *parent=nullptr);
    ~OpenCVItem();
    virtual void renderTo(QImage &)=0;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *,QWidget *) override;
    void closeEvent(QCloseEvent *) override;
signals:
    void onCloseEventCalled(OpenCVItem*);
private:
    void _onYChanged();
    void _onXChanged();
public slots:
    virtual void saveImage();
    virtual void onYChanged();
    virtual void onXChanged();
};

#endif // OPENCVITEM_HPP
