#include "ui_ControlItem.h"
#include "ControlItem.hpp"
#include <QtWidgets/qboxlayout.h>
#include <OpenCVImageItem.hpp>
#include <opencv2/opencv.hpp>

ControlItem::~ControlItem(){
    delete ui;
}

namespace {
const constexpr cv::TemplateMatchModes index2Mode[]{
    cv::TM_SQDIFF,
    cv::TM_SQDIFF_NORMED,
    cv::TM_CCORR,
    cv::TM_CCORR_NORMED,
    cv::TM_CCOEFF,
    cv::TM_CCOEFF_NORMED,
};
}

int ControlItem::getMode()const {
    return index2Mode[ui->mode_select->currentIndex()];
}

ControlItem::ControlItem(OpenCVImageItem *arg_i,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    rootItem_=arg_i;
    ui->setupUi(this);
    this->setLayout(ui->thisLayout);
    this->setMinimumWidth(256);
    this->setMinimumHeight(256);
}

namespace {
QSize eval_best_size(QSize size_input) {
    if ((size_input.width()<=256)&&
        (size_input.height()<=256)
        ) {
        return size_input;
    }

    if (size_input.width()==size_input.height()) {
        return{256,256};
    }

    if (size_input.width()>size_input.height()) {
        auto newHeight=
            double(size_input.height())/size_input.width()*256.0;
        return{256,qRound(newHeight)};
    }
    else {
        auto newWidth=
            double(size_input.width())/size_input.height()*256.0;
        return{qRound(newWidth),256};
    }

}
}

void ControlItem::_p_update_template_image_show_() {
    auto * s=ui->template_image_view->scene();

    if (s==nullptr) {
        s=new QGraphicsScene(this);
        ui->template_image_view->setScene(s);
    }

    if (template_image_show_) {
        s->removeItem(template_image_show_);
        delete template_image_show_;
        template_image_show_=nullptr;
    }

    {
        auto to_size_=eval_best_size(template_image_.size());
        template_image_show_=new QGraphicsPixmapItem(
            QPixmap::fromImage(
            template_image_.scaled(to_size_,
            Qt::AspectRatioMode::IgnoreAspectRatio,
            Qt::TransformationMode::SmoothTransformation)));
    }

    s->addItem(template_image_show_);
    s->setSceneRect(template_image_show_->boundingRect());
    s->sceneRectChanged(s->sceneRect());
}

