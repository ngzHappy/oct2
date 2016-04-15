#include "../OpenCVVerticalItems.hpp"
#include <QtWidgets/qgraphicslinearlayout.h>
#include <QtCore/qdebug.h>
#include <QtWidgets/qgraphicsscene.h>
#include <QtWidgets/qgraphicsproxywidget.h>
#include <QtGui/qpainter.h>

OpenCVVerticalItems::OpenCVVerticalItems(QGraphicsItem *parent)
    :P(parent)
{
    layout_=new QGraphicsLinearLayout(Qt::Orientation::Vertical);
    this->setLayout(layout_);
    layout_->setSpacing(0);
    layout_->setContentsMargins(0,0,0,0);
    layout_->addStretch(1);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setMinimumHeight(64);
    this->setMinimumWidth(128);
}

OpenCVVerticalItems::~OpenCVVerticalItems()
{

}

void OpenCVVerticalItems::addItem(QGraphicsLayoutItem *item_){
    if(item_==nullptr){return;}
    auto count_=layout_->count();
    return layout_->insertItem(count_,item_)/*insert before stretch*/;
}

QGraphicsProxyWidget * OpenCVVerticalItems::addWidget(QWidget * p){
    if(p==nullptr){return nullptr;}
    if(this->scene()==nullptr){
        qDebug().noquote()<<__LINE__<<__FILE__<<__func__;
        p->deleteLater();
    }
    QGraphicsScene * scene_=this->scene();
    QGraphicsProxyWidget * item_ =scene_->addWidget(p);
    auto count_=layout_->count();
    layout_->insertItem(count_,item_)/*insert before stretch*/;
    return item_;
}

void OpenCVVerticalItems::onXChanged() {
    qreal t_[1],b_[1],l_[1],r_[1];
    this->getWindowFrameMargins(l_,t_,r_,b_);
    l_[0]-=512;
    if (x()>=(l_[0])) { return; }
    setPos(l_[0],y());
}

void OpenCVVerticalItems::onYChanged() {
    qreal t_[1],b_[1],l_[1],r_[1];
    this->getWindowFrameMargins(l_,t_,r_,b_);
    t_[0]-=512;
    if (y()>=(t_[0])) { return; }
    setPos(x(),(t_[0]));
}

void OpenCVVerticalItems::renderTo(QImage &i){
    auto * chart_=this;
    if (chart_) {

        QSizeF csize_=chart_->size();
        i=QImage(
                    qRound(csize_.width()+0.51),qRound(csize_.height()+0.51),
                    QImage::Format_RGBA8888
                    );
        i.fill(QColor(0,0,0,0));

        QGraphicsScene * sc_=chart_->scene();
        if (sc_==nullptr) { return; }
        sc_->setActiveWindow(this);

        QPointF spos_=chart_->mapToScene(chart_->rect().topLeft());

        QPainter painter(&i);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        sc_->render(
                    &painter,
                    QRectF(0,0,i.width(),i.height()),
                    QRectF(spos_.x(),spos_.y(),i.width(),i.height())
                    );

    }
}


