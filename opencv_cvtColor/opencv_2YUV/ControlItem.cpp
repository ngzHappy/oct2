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
    pack->y=ui->yDoubleSpinBox->value();
    pack->yBase=ui->yBaseDoubleSpinBox->value();
    pack->u=ui->uDoubleSpinBox->value();
    pack->uBase=ui->uBaseDoubleSpinBox->value();
    pack->v=ui->vDoubleSpinBox->value();
    pack->vBase=ui->vBaseDoubleSpinBox->value();
}

ControlItem::~ControlItem()
{
    delete ui;
}

