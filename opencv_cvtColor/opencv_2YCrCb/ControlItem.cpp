#include "ControlItem.hpp"
#include "ui_ControlItem.h"

ControlItem::ControlItem(
        OpenCVImageItem * arg_i,
        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlItem),
    rootItem_(arg_i)
{
    ui->setupUi(this);
}

void ControlItem::_p_init_pack(Pack *pack){
    pack->cb=ui->cbDoubleSpinBox->value();
    pack->cbBase=ui->cbBaseDoubleSpinBox->value();
    pack->cr=ui->crDoubleSpinBox->value();
    pack->crBase=ui->crBaseDoubleSpinBox->value();
    pack->y=ui->yDoubleSpinBox->value();
    pack->yBase=ui->yBaseDoubleSpinBox->value();
}

ControlItem::~ControlItem()
{
    delete ui;
}

