﻿#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

#include <QtWidgets/QWidget>
class OpenCVImageItem;
namespace Ui {
class ControlItem;
}

class ControlItem : public QWidget
{
    Q_OBJECT

public:

    class Pack{
    public:
        double rho;
        double theta;
        int threshold;
        double srn;
        double stn;
        double min_theta;
        double max_theta;
    };

    ControlItem(OpenCVImageItem *,QWidget *parent = 0);
    ~ControlItem();

private slots:
    void on_select_image_button_clicked();
    void on_do_button_clicked();

private:
    Ui::ControlItem *ui;
    OpenCVImageItem * rootItem_;
    void _p_init_pack(Pack*);
};

#endif // CONTROLITEM_HPP
