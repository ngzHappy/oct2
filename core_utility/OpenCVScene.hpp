#ifndef OPENCVSCENE_HPP
#define OPENCVSCENE_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include <QtWidgets/qgraphicsscene.h>
#include <QtCore/qpointer.h>
#include <QtWidgets/qgraphicsitem.h>
#include "OpenCVImageItem.hpp"
#include "OpenCVHistItem.hpp"
#include "OpenCVScatterItem.hpp"
#include "OpenCVLineSeriesItem.hpp"
#include "OpenCVChartImage.hpp"
#include "core_utility_global.hpp"

class CORE_UTILITYSHARED_EXPORT OpenCVScene : public QGraphicsScene {
    Q_OBJECT
private:
    typedef QGraphicsScene P;
public:
    explicit OpenCVScene(QObject * /**/=nullptr);
    ~OpenCVScene();
    void setImageAlg(const OpenCVImageItem::AlgFunctionType &);
    OpenCVImageItem * insertImage(QImage);
    OpenCVHistItem * insertHist(QList<qreal>);
    OpenCVScatterItem * insertScatter(QList<QPointF>);
    OpenCVLineSeriesItem * insertLineSeries(QList<QPointF>);
    OpenCVChartImage * insertChartImage(QImage);
    template<typename B,typename E>
    OpenCVHistItem * insertHist(B,E);
protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent) override;
private:
    void _p_private__insert_image(QImage &image_);
};

template<typename B,typename E>
OpenCVHistItem * OpenCVScene::insertHist(B b,E e) {
    QList<qreal> ans_;
    for (; b!=e; ++b) { ans_.push_back(*b); }
    return insertHist(std::move(ans_));
}


#endif // OPENCVSCENE_HPP
