﻿#include "OpenCVWindow.hpp"
#include "../core_utility.hpp"
#include "QtGui/qicon.h"

OpenCVWindow::OpenCVWindow(QWidget *parent)
    :P(parent),
    scene_(new OpenCVScene) {
    delete this->scene();
    this->setScene(scene_);
    scene_->setParent(this);
    this->resize(512,512);
    scene_->setBackgroundBrush(QColor(200-30,200-15,200-10));
    this->setWindowIcon(QIcon());

    setRenderHint( QPainter::HighQualityAntialiasing,true );
    setRenderHint( QPainter::SmoothPixmapTransform,true );
    setRenderHint( QPainter::TextAntialiasing,true );
    setRenderHint( QPainter::Antialiasing,true );
}

OpenCVWindow::~OpenCVWindow() {

}

void OpenCVWindow::setImageAlg(const OpenCVImageItem::AlgFunctionType & a) {
    this->setUpdatesEnabled(false);
    this->viewport()->setUpdatesEnabled(false);
    scene_->setImageAlg(a);
    this->setUpdatesEnabled(true);
    this->viewport()->setUpdatesEnabled(true);
    this->viewport()->update();
}

void OpenCVWindow::resizeEvent(QResizeEvent *event) {
    P::resizeEvent(event);
    qreal width_=this->width();
    qreal height_=this->height();
    auto sr_=scene_->sceneRect();
    width_=(std::max<qreal>)(width_,sr_.width());
    height_=(std::max<qreal>)(height_,sr_.height());
    QRectF sr__(0,0,width_,height_);
    if (sr__==sr_) { return; }
    scene_->setSceneRect(sr__);
}
