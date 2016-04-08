/*MainWindow.cpp*/
#include <OpenCVUtility.hpp>
#include <QtWidgets/qgraphicsproxywidget.h>
#include <QtWidgets/qgraphicslinearlayout.h>
#include "MainWindow.hpp"
#include "OpenCVWindowDetail.hpp"
#include <QtCore/qdebug.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qslider.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qgraphicsitem.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qmenubar.h>

namespace {
namespace __private {

class SpinSlider {
public:
    QSpinBox * spinbox=nullptr;
    QSlider * slider=nullptr;
    void reate(QVBoxLayout *);
    void setRange(int min_,int max_) {
        if (slider==nullptr) { return; }
        if (spinbox==nullptr) { return; }
        if (min_>max_) { std::swap(max_,min_); }
        spinbox->setRange(min_,max_);
        slider->setRange(min_,max_);
        slider->setSingleStep(1);
        spinbox->setSingleStep(1);
    }
};

}
}

namespace {
namespace __private {
class WindowTitleBar :public QWidget {
public:
    SpinSlider xPos_;
    SpinSlider yPos_;
    SpinSlider width_;
    SpinSlider height_;

    WindowTitleBar() {
        QVBoxLayout * layout_=new QVBoxLayout;
        xPos_.reate(layout_);
        yPos_.reate(layout_);
        width_.reate(layout_);
        height_.reate(layout_);
        setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setMargin(0);
        xPos_.slider->setValue(0);
        yPos_.slider->setValue(0);
        width_.slider->setValue(100);
        height_.slider->setValue(100);
    }

};

}
}

namespace {
namespace __private {

class RectItem :
    public QGraphicsWidget {
    QBrush brush_;
    QPen pen_;
public:
    RectItem(QGraphicsItem * p): QGraphicsWidget(p) {
        {
            QPalette pal=this->palette();
            pal.setBrush(QPalette::Background,Qt::transparent);
            this->setPalette(pal);
        }
        this->setFlag(QGraphicsItem::ItemIsMovable);
    }

    void setBrush(const QBrush &v) { brush_=v; update(); }
    void setPen(const QPen &v) { pen_=v; update(); }

    void paint(QPainter * p,const QStyleOptionGraphicsItem *,
        QWidget *)override {
        p->setPen(pen_);
        p->setBrush(brush_);
        p->drawRect(rect());
    }

};

}
}

/*中央窗口*/
namespace {
namespace __private {
class CentralWidget :public QWidget {
    QVBoxLayout * layout_;
public:
    CentralWidget(OpenCVWindow * window) {
        layout_=new QVBoxLayout;
        this->setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setMargin(0);
        layout_->addWidget(window);
    }
    ~CentralWidget() {}
};

void SpinSlider::reate(QVBoxLayout * l) {
    QHBoxLayout * hl=new QHBoxLayout;
    l->addLayout(hl);
    spinbox=new QSpinBox;
    slider=new QSlider(Qt::Horizontal);
    hl->addWidget(spinbox);
    hl->addWidget(slider);
    hl->setSpacing(0);
    hl->setMargin(0);

    typedef void(QSpinBox::*TT)(int);
    QObject::connect(slider,&QSlider::valueChanged,spinbox,&QSpinBox::setValue);
    QObject::connect(spinbox,TT(&QSpinBox::valueChanged),slider,&QSlider::setValue);
}

}
}

namespace {
namespace __private {

class MainWindow :public QMainWindow {
    OpenCVImageItem * imageItem_;
    RectItem * rectItem_;
    WindowTitleBar * titleBar_;
    QAction * openImage_;
    QAction * saveImage_;
public:

    MainWindow() {
        titleBar_=new WindowTitleBar;
        setCentralWidget(titleBar_);
        openImage_=menuBar()->addAction(trUtf8(u8"打开图片"));
        saveImage_=menuBar()->addAction(trUtf8(u8"保存"));
        connect(openImage_,&QAction::triggered,this,[this](bool) {open(); });
        connect(saveImage_,&QAction::triggered,this,[this](bool) {save(); });
    }

    void save();
    void open();

    void resetSize(OpenCVImageItem * i) {
        auto h_=this->height()+i->image().height();
        auto ih_=i->minimumHeight();
        i->setMinimumHeight((h_>ih_)?h_:ih_);
        titleBar_->xPos_.setRange(0,i->image().width());
        titleBar_->yPos_.setRange(0,i->image().height());
        titleBar_->width_.setRange(1,std::max(1,i->image().width()));
        titleBar_->height_.setRange(1,std::max(1,i->image().height()));
    }

    void create(OpenCVImageItem * i) {
        imageItem_=i;
        rectItem_=new RectItem(i->getImageItem());
        rectItem_->setGeometry({ 0,0,100.0f,100.0f });
        rectItem_->setBrush(QColor(200,30,60,130));
        rectItem_->setPen(QPen(QColor(30,50,200,200),2));

        connect(titleBar_->xPos_.slider,&QSlider::valueChanged,this,[this](int) {setRectPos(); });
        connect(titleBar_->yPos_.slider,&QSlider::valueChanged,this,[this](int) {setRectPos(); });
        connect(titleBar_->width_.slider,&QSlider::valueChanged,this,[this](int) {setRectPos(); });
        connect(titleBar_->height_.slider,&QSlider::valueChanged,this,[this](int) {setRectPos(); });
        connect(rectItem_,&QGraphicsWidget::geometryChanged,this,[this]() {updateTitleBar(); });
    }

    bool isUpdateTitleBar=false;
    void updateTitleBar() {
        if (isUpdateTitleBar) { return; }
        isUpdateTitleBar=true;
        try {
            auto g_=rectItem_->geometry();
            if (g_.x()!=titleBar_->xPos_.slider->value()) {
                titleBar_->xPos_.slider->setValue(qRound(g_.x()));
            }
            if (g_.y()!=titleBar_->yPos_.slider->value()) {
                titleBar_->yPos_.slider->setValue(qRound(g_.y()));
            }
        }
        catch (...) {/*???*/ }
        isUpdateTitleBar=false;
    }

    void setRectPos() {
        if (isUpdateTitleBar) { return; }
        int x_=titleBar_->xPos_.slider->value();
        int y_=titleBar_->yPos_.slider->value();
        int w_=titleBar_->width_.slider->value();
        int h_=titleBar_->height_.slider->value();
        rectItem_->setGeometry(x_,y_,w_,h_);
    }

};

void MainWindow::save() {

    const QString saveFileName__=QFileDialog::getSaveFileName();
    if (saveFileName__.isEmpty()) { return; }
    QImage image__=imageItem_->image()/*获取原始图像*/;
    QRectF roiRect__=rectItem_->geometry()/*获得roi rect*/;
    QRectF imageRect__(0,0,image__.width(),image__.height())/*获得image rect*/;
    roiRect__&=imageRect__/*计算roi区域*/;
    if (roiRect__.isEmpty()==false) {
        auto cvMat__=OpenCVUtility::tryRead(image__);
        cv::Mat ans__;
        ans__=cvMat__(cv::Rect2f(
            roiRect__.x(),
            roiRect__.y(),
            roiRect__.width(),
            roiRect__.height()))/*执行roi*/;
        auto aboutSave__=OpenCVUtility::tryRead(ans__);
        aboutSave__.save(saveFileName__);
    }
    else {
        qDebug()<<"roi is null";
    }

}

void MainWindow::open() {

    const QString files_=QFileDialog::getOpenFileName(
        nullptr,
        u8R"(选择图片)"_qs,
        ""/*dir*/,
        ""/*filter*/
        );

    if (files_.isEmpty()==false) {
        imageItem_->setImage(QImage(files_));
    }

}

}
}

namespace {
namespace __private {

void create(OpenCVImageItem *  itemWidget) {

    QGraphicsScene * scene_=itemWidget->scene();
    if (scene_==0) { return; }

    __private::MainWindow * tbar=new __private::MainWindow;
    auto * dtbar=scene_->addWidget(tbar);

    tbar->create(itemWidget);

    QGraphicsLinearLayout * layout_=new QGraphicsLinearLayout(Qt::Vertical);
    itemWidget->setLayout(layout_);

    layout_->addItem(dtbar);

    itemWidget->getImageItem()->setParentItem(nullptr);
    itemWidget->getImageItem()->setParent(nullptr);
    layout_->addItem(itemWidget->getImageItem());

    layout_->addStretch();
    layout_->setSpacing(0);
    layout_->setContentsMargins(0,0,0,0);

    QObject::connect(itemWidget,&OpenCVImageItem::imageChanged,
        tbar,[itemWidget,tbar]() {tbar->resetSize(itemWidget); }
    );
    tbar->resetSize(itemWidget);
}

}
}

OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i) {
    OpenCVImageItem * ans=P::insertImage(std::move(i));
    __private::create(ans);
    return ans;
}

/*初始化主窗口*/
MainWindow::MainWindow(QWidget *parent):
    P(parent) {
    openCVWindow_=new OpenCVWindowDetail;
    this->setCentralWidget(new __private::CentralWidget(openCVWindow_));
    this->setMinimumSize(512,512);
    this->resize(600,600);
    QAction * openImage_=menuBar()->addAction(trUtf8(u8"打开图片"));
    connect(openImage_,&QAction::triggered,this,[this](bool) {openImage(); });
}

void MainWindow::openImage() {
    const QString files_=QFileDialog::getOpenFileName(
        nullptr,
        u8R"(选择图片)"_qs,
        ""/*dir*/,
        ""/*filter*/
        );

    if (files_.isEmpty()) { return; }
    getOpenCVWindow()->insertImage( QImage(files_) );

}

/*析构主窗口*/
MainWindow::~MainWindow() {

}

