#include "ControlItem.hpp"
#include "ui_ControlItem.h"

ControlItem::ControlItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlItem)
{
    ui->setupUi(this);
}

ControlItem::~ControlItem()
{
    delete ui;
}
