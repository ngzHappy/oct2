#include "ControlItem.hpp"
#include "ui_ControlItem.h"

ControlItem::ControlItem(OpenCVImageItem *arg_i, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlItem),
    rootItem_(arg_i)
{
    ui->setupUi(this);
}

 void ControlItem::_p_init_pack(Pack * pack){

 }

ControlItem::~ControlItem()
{
    delete ui;
}


