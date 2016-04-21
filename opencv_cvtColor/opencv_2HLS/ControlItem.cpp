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
    pack->hBase=ui->hBaseDoubleSpinBox->value();
    pack->lBase=ui->lBaseDoubleSpinBox->value();
    pack->sBase=ui->sBaseDoubleSpinBox->value();
    pack->h=ui->hDoubleSpinBox->value();
    pack->l=ui->lDoubleSpinBox->value();
    pack->s=ui->sDoubleSpinBox->value();
}

ControlItem::~ControlItem()
{
    delete ui;
}

