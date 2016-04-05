#include "OpenCVItem.hpp"
#include "OpenCVStyle.hpp"
#include <QtGui/qpalette.h>
#include <QtWidgets/qstyleoption.h>
#include <QtGui/qpainter.h>
#include <QtWidgets/qgraphicsproxywidget.h>
#include <QtWidgets/qgraphicslinearlayout.h>
#include <QtWidgets/qgraphicsgridlayout.h>
#include <QtCore/qdebug.h>
#include <QtWidgets/qproxystyle.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qgraphicssceneevent.h>

namespace {
namespace __private {
class OpenCVItemStyle :public OpenCVStyle {
    typedef OpenCVStyle P;
public:

    static const QIcon & getTitleBarIcon() {
        static const QIcon ans_=[]() {
            enum { R_=128,R_0_=R_/4,R_1_=2*R_/4,R_2_=3*R_/4 };
            QImage image_(R_,R_,QImage::Format_RGBA8888);
            image_.fill(QColor(0,0,0,0));
            QPainter painter(&image_);

            QPen pen(QColor(9,0,9,0),0);
            painter.setPen(pen);

            painter.setRenderHint(QPainter::HighQualityAntialiasing);

            QPainterPath  p1,p2,p3;

            {
                p1.addEllipse((R_-R_2_)/2,(R_-R_2_)/2,R_2_,R_2_);
                p1.addEllipse((R_-R_1_)/2,(R_-R_1_)/2,R_1_,R_1_);
            }

            {
                p2.addEllipse((R_-R_1_)/2,(R_-R_1_)/2,R_1_,R_1_);
                p2.addEllipse((R_-R_0_)/2,(R_-R_0_)/2,R_0_,R_0_);
            }

            {
                p3.addEllipse((R_-R_0_)/2,(R_-R_0_)/2,R_0_,R_0_);
            }

            painter.setBrush(QColor(0,0,255,160));
            painter.drawPath(p3);
            painter.setBrush(QColor(0,255,0,160));
            painter.drawPath(p2);
            painter.setBrush(QColor(255,0,0,160));
            painter.drawPath(p1);

            return QIcon(QPixmap::fromImage(std::move(image_)));
        }();
        return ans_;
    }

    void drawComplexControl(
        ComplexControl control,
        const QStyleOptionComplex *option,
        QPainter *painter,
        const QWidget *widget) const {

        if (control==ComplexControl::CC_TitleBar) {
            const auto * titileBarStyle_=qstyleoption_cast<const QStyleOptionTitleBar *>(option);
            if (titileBarStyle_) {
                auto tbstyle_=const_cast<QStyleOptionTitleBar *>(titileBarStyle_);
                tbstyle_->icon=getTitleBarIcon();
            }
        }

        return P::drawComplexControl(control,option,painter,widget);
    }

    OpenCVItemStyle() {}
};
}
}

OpenCVItem::OpenCVItem(QGraphicsItem *parent)
    :P(parent,Qt::Window) {

    static OpenCVStyle * style_=nullptr;
    if (style_==nullptr) {
        style_=new __private::OpenCVItemStyle/*construct by default style*/;
        qAddPostRoutine([]() {delete style_; style_=nullptr; });
    }

    this->setStyle(style_);

    {
        QPalette pal=this->palette();
        pal.setBrush(QPalette::Background,Qt::transparent);
        this->setPalette(pal);
    }

    this->resize(128,128);
    this->setMinimumWidth(128);
    this->setMinimumHeight(128);
    this->setPos(std::rand()&63,(std::rand()&63)+36);
    this->setAttribute(Qt::WA_DeleteOnClose);

    connect(this,&OpenCVItem::yChanged,this,[this]() {_onYChanged(); });
    connect(this,&OpenCVItem::xChanged,this,[this]() {_onXChanged(); });
}

OpenCVItem::~OpenCVItem() {
}

void OpenCVItem::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget) {
    P::paint(painter,option,widget);
}

void OpenCVItem::_onXChanged() {
    qreal t_[1],b_[1],l_[1],r_[1];
    this->getWindowFrameMargins(l_,t_,r_,b_);
    if (x()>=(l_[0])) { return; }
    setPos(l_[0],y());
}

void OpenCVItem::_onYChanged() {
    qreal t_[1],b_[1],l_[1],r_[1];
    this->getWindowFrameMargins(l_,t_,r_,b_);
    if (y()>=(t_[0])) { return; }
    setPos(x(),(t_[0]));
}

void OpenCVItem::mousePressEvent(
        QGraphicsSceneMouseEvent *event
        ) {
    return P::mousePressEvent(event);
}
