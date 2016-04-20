#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

#include <QtWidgets/QWidget>

namespace Ui {
class ControlItem;
}

class ControlItem : public QWidget
{
    Q_OBJECT

public:
    explicit ControlItem(QWidget *parent = 0);
    ~ControlItem();

private slots:
    void on_do_button_clicked();

    void on_select_image_button_clicked();

private:
    Ui::ControlItem *ui;
};

#endif // CONTROLITEM_HPP
