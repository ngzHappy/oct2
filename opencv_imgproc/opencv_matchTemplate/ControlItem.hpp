#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

namespace Ui {
    class Form;
} // namespace Ui
#include <QtWidgets/QWidget>
#include <QImage>
class OpenCVImageItem;

class ControlItem : public QWidget
{
    Q_OBJECT
public:
    explicit ControlItem(OpenCVImageItem *,QWidget *parent = 0);
    ~ControlItem();

signals:

public slots:

private slots:

private:
    Ui::Form * ui;
    OpenCVImageItem * rootItem_;
    QImage template_image_;
};

#endif // CONTROLITEM_HPP
