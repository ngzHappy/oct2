#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#include "../OpenCVItem.hpp"
#include "../OpenCVStyle.hpp"
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
#include <QtWidgets/qfiledialog.h>
#include <atomic>
#include <QtCore/qdebug.h>

namespace {
namespace __private {
class OpenCVItemStyle :public OpenCVStyle {
    typedef OpenCVStyle P;
public:
    static std::atomic<int> icon_index;
    static const QIcon getTitleBarIcon() {
        /*通过此函数调整随机数*/
        auto icon_function_ =[](int rand_flag_) {
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

            switch_flag_:
            switch (rand_flag_) {
                case 0: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p1);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p2);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p3);
                }break;
                case 1: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p2);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p1);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p3);
                case 2: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p2);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p3);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p1);
                }break;
                }break;
                case 3: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p3);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p2);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p1);
                }break;
                case 4: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p3);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p1);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p2);
                }break;
                case 5: {
                    painter.setBrush(QColor(rand()&63,rand()&63,255,160+(rand()&15)));
                    painter.drawPath(p1);
                    painter.setBrush(QColor(rand()&63,255,rand()&63,160+(rand()&15)));
                    painter.drawPath(p3);
                    painter.setBrush(QColor(255,rand()&63,rand()&63,160+(rand()&15)));
                    painter.drawPath(p2);
                }break;
                default: {
                    rand_flag_=11-rand_flag_;
                    goto switch_flag_;
                }
            }

            return QIcon(QPixmap::fromImage(std::move(image_)));
        } ;

        static QIcon ans_[12];
        static bool init_icon_=[icon_function_]() {
            ans_[0]=icon_function_(0);
            ans_[1]=icon_function_(1);
            ans_[2]=icon_function_(2);
            ans_[3]=icon_function_(3);
            ans_[4]=icon_function_(4);
            ans_[5]=icon_function_(5);
            ans_[6]=icon_function_(6);
            ans_[7]=icon_function_(7);
            ans_[8]=icon_function_(8);
            ans_[9]=icon_function_(9);
            ans_[10]=icon_function_(10);
            ans_[11]=icon_function_(11);
            return (rand()==8);
        }();
        ++icon_index;
        if (icon_index>11) { icon_index=0; }
        return ans_[std::min(icon_index.load(),11)];
        (void)(init_icon_);
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

    OpenCVItemStyle() {
    }
};

std::atomic<int> OpenCVItemStyle::icon_index{0};

}
}

/*change here to set opencv window color*/
OpenCVStyle * OpenCVStyle::instance() {
    static OpenCVStyle * style_=nullptr;
    if (style_==nullptr) {
        style_=new __private::OpenCVItemStyle/*construct by default style*/;
        qAddPostRoutine([]() {delete style_; style_=nullptr; });
    }
    return style_;
}

void OpenCVItem::renderTo(QImage &) {}

void OpenCVItem::saveImage() {
    {
        const QGraphicsScene * sc__=this->scene();
        if (sc__==nullptr) { return; }
    }

    {
        const QString saveFileName_=
            QFileDialog::getSaveFileName(nullptr,
                trUtf8(u8"设置保存文件名"),
                QString(),
                "Images (*.png *.jpg)"
                );
        if (saveFileName_.isEmpty()) { return; }
        QImage _chart_image_;
        renderTo(_chart_image_);
        _chart_image_.save(saveFileName_);
    }
}

OpenCVItem::OpenCVItem(QGraphicsItem *parent)
    :P(parent,Qt::Window) {

    OpenCVStyle * style_=OpenCVStyle::instance();
    this->setStyle(style_);

    {/*style*/
        QPalette pal=this->palette();
        pal.setColor(
            QPalette::Background,
            style_->opencvWindowBackGroundColor()
            );
        this->setPalette(pal);
    }

    {
        this->setFlag(QGraphicsItem::ItemDoesntPropagateOpacityToChildren,true);
        this->setFlag(QGraphicsItem::ItemClipsChildrenToShape,true);
        this->setAutoFillBackground(false)/*add draw speed*/;
    }

    this->resize(132,132);
    this->setMinimumWidth(130);
    this->setMinimumHeight(130);
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
