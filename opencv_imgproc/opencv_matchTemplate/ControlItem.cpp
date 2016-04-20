#include "ui_ControlItem.h"
#include "ControlItem.hpp"
#include <QtWidgets/qboxlayout.h>

ControlItem::~ControlItem(){}

ControlItem::ControlItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    QHBoxLayout * layout_=new QHBoxLayout;
    this->setLayout(layout_);
    layout_->setSpacing(0);
    layout_->setMargin(0);
    layout_->addWidget(ui);
}

