#include "ControlItem.hpp"
#include "ui_ControlItem.h"

ControlItem::ControlItem(OpenCVImageItem * arg_i, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlItem),
    rootItem_(arg_i)
{
    ui->setupUi(this);
}

void ControlItem::_p_init_pack(Pack * pack){
    pack->maxLineGap=ui->maxLineGapDoubleSpinBox->value();
    pack->minLineLength=ui->minLineLengthDoubleSpinBox->value();
    pack->rho=ui->rhoDoubleSpinBox->value();
    pack->theta=ui->thetaDoubleSpinBox->value();
    pack->threshold=ui->thresholdSpinBox->value();
}

ControlItem::~ControlItem()
{
    delete ui;
}


