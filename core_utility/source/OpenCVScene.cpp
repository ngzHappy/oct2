﻿#include "OpenCVScene.hpp"
#include <QtWidgets/qgraphicssceneevent.h>

namespace {
namespace __private {
constexpr float inline bottom() { return 0; }
constexpr float inline top() { return 1; }
constexpr float inline middle() { return 0.5; }
}
}

OpenCVScene::OpenCVScene(QObject * p):P(p) {

}

OpenCVScene::~OpenCVScene() {

}

void OpenCVScene::contextMenuEvent(
    QGraphicsSceneContextMenuEvent *contextMenuEvent
    ) {

    const QPoint pos_=contextMenuEvent->screenPos();
    QGraphicsItem * item_=this->itemAt(contextMenuEvent->scenePos(),QTransform());
    if(item_==nullptr){return;}
    OpenCVImageItem * imageItem_=dynamic_cast<OpenCVImageItem *>(item_);
    if (imageItem_==nullptr) {
        imageItem_=dynamic_cast<OpenCVImageItem *>(item_->parentItem());
    }

    if (imageItem_) {
        QMenu menu_;
        QAction * action_=menu_.addAction(trUtf8(u8R"(保存)"));
        connect(action_,&QAction::triggered,
            imageItem_,[imageItem_](bool) {imageItem_->saveImage(); });
        menu_.exec(pos_);
    }

}

void OpenCVScene::setImageAlg(const OpenCVImageItem::AlgFunctionType & a) {
    QList<QGraphicsItem *> allitems_=this->items();
    for (QGraphicsItem * i:allitems_) {
        OpenCVImageItem * image_item_=dynamic_cast<OpenCVImageItem *>(i);
        if (image_item_) { image_item_->setAlgFunction(a); }
    }
}

OpenCVImageItem * OpenCVScene::insertImage(QImage image_) {
    if ((image_.width()<=0)||(image_.height()<=0)) {
        image_=QImage(512,512,QImage::Format_ARGB32);
        image_.fill(QColor(0,0,0,0));
        QPainter painter_(&image_);
        QFont font_=painter_.font();
        font_.setPixelSize(36);
        painter_.setFont(font_);
        painter_.setPen(QPen(QColor(255,5,0),1));
        painter_.setBrush(QColor(255,5,0));
        painter_.drawText(55,200,"NULL IMAGE");
    }
    OpenCVImageItem * i=new OpenCVImageItem;
    i->setImage(std::move(image_));
    addItem(i);
    return i;
}

OpenCVLineSeriesItem * OpenCVScene::insertLineSeries(QList<QPointF> data_) {
    OpenCVLineSeriesItem * i=new OpenCVLineSeriesItem;
    i->setData(std::move(data_));
    addItem(i);
    return i;
}

OpenCVScatterItem * OpenCVScene::insertScatter(QList<QPointF> data_) {
    OpenCVScatterItem * i=new OpenCVScatterItem;
    i->setData(std::move(data_));
    addItem(i);
    return i;
}

OpenCVHistItem * OpenCVScene::insertHist(QList<qreal> data_) {
    OpenCVHistItem * i=new OpenCVHistItem;
    i->setData(std::move(data_));
    addItem(i);
    return i;
}



