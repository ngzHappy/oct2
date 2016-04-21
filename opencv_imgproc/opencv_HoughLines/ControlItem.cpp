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
    pack->rho=ui->rhoDoubleSpinBox->value();
    pack->theta=ui->thetaDoubleSpinBox->value();
    pack->threshold=ui->thresholdSpinBox->value();
    pack->srn=ui->srnDoubleSpinBox->value();
    pack->stn=ui->stnDoubleSpinBox->value();
    pack->min_theta=ui->min_thetaDoubleSpinBox->value();
    pack->max_theta=ui->max_thetaDoubleSpinBox->value();
}
