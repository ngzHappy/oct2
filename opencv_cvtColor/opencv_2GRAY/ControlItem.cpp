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
    pack->r=ui->rDoubleSpinBox->value();
    pack->g=ui->gDoubleSpinBox->value();
    pack->b=ui->bDoubleSpinBox->value();
    pack->rBase=ui->rBaseDoubleSpinBox->value();
    pack->gBase=ui->gBaseDoubleSpinBox->value();
    pack->bBase=ui->bBaseDoubleSpinBox->value();
}

ControlItem::~ControlItem()
{
    delete ui;
}

