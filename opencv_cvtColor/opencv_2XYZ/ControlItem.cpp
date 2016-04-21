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
    pack->x=ui->xDoubleSpinBox->value();
    pack->y=ui->yDoubleSpinBox->value();
    pack->z=ui->zDoubleSpinBox->value();

    pack->xBase=ui->xBaseDoubleSpinBox->value();
    pack->yBase=ui->yBaseDoubleSpinBox->value();
    pack->zBase=ui->zBaseDoubleSpinBox->value();
}

ControlItem::~ControlItem()
{
    delete ui;
}

