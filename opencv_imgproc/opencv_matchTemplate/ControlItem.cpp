#include "ui_ControlItem.h"
#include "ControlItem.hpp"
#include <QtWidgets/qboxlayout.h>
#include <OpenCVImageItem.hpp>

ControlItem::~ControlItem(){
    delete ui;
}

ControlItem::ControlItem(OpenCVImageItem *arg_i,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    rootItem_=arg_i;
    ui->setupUi(new QWidget);
    this->setLayout(ui->thisLayout);
    this->setMinimumWidth(128);
    this->setMinimumHeight(64);
}

