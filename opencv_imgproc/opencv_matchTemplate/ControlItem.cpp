#include "ui_ControlItem.h"
#include "ControlItem.hpp"
#include <QtWidgets/qboxlayout.h>

ControlItem::~ControlItem(){
    delete ui;
}

ControlItem::ControlItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(new QWidget);
    this->setLayout(ui->thisLayout);
    this->setMinimumWidth(128);
    this->setMinimumHeight(64);
}

