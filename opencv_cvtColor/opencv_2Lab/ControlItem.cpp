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
    pack->l=ui->lDoubleSpinBox->value();
    pack->lBase=ui->lBaseDoubleSpinBox->value();
    pack->a=ui->aDoubleSpinBox->value();
    pack->aBase=ui->aBaseDoubleSpinBox->value();
    pack->b=ui->bDoubleSpinBox->value();
    pack->bBase=ui->bBaseDoubleSpinBox->value();
}

ControlItem::~ControlItem()
{
    delete ui;
}

