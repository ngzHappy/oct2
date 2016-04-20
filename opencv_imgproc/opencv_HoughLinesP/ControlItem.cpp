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

void ControlItem::on_do_button_clicked()
{

}

void ControlItem::on_select_image_button_clicked()
{

}
