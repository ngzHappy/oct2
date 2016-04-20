#include "ControlItem.hpp"
#include "ui_ControlItem.h"

ControlItem::ControlItem(OpenCVImageItem *arg_i, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlItem),
    rootItem_(arg_i)
{
    ui->setupUi(this);
}

ControlItem::~ControlItem()
{
    delete ui;
}

 void ControlItem::_p_init_pack(Pack* pack){
     pack->dp=ui->dpDoubleSpinBox->value();
     pack->maxRadius=ui->maxRadiusSpinBox->value();
     pack->method=3/*HOUGH_GRADIENT*/;
     pack->minDist=ui->minDistDoubleSpinBox->value();
     pack->minRadius=ui->minRadiusSpinBox->value();
     pack->param1=ui->param1DoubleSpinBox->value();
     pack->param2=ui->param2DoubleSpinBox->value();
 }
