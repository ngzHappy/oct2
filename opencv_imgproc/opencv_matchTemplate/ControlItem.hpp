#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

namespace Ui {
    class Form;
} // namespace Ui
#include <QtWidgets/QWidget>

class ControlItem : public QWidget
{
    Q_OBJECT
public:
    explicit ControlItem(QWidget *parent = 0);
    ~ControlItem();

signals:

public slots:

private slots:

private:
    Ui::Form * ui;
};

#endif // CONTROLITEM_HPP
