#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

namespace Ui {
    class Form;
} // namespace Ui
#include <QtWidgets/QWidget>
#include <QImage>
#include <QtWidgets/qgraphicsitem.h>
class OpenCVImageItem;

class ControlItem : public QWidget
{
    Q_OBJECT
public:
    explicit ControlItem(OpenCVImageItem *,QWidget *parent = 0);
    ~ControlItem();

    int getMode()const;
signals:

public slots:
 
private slots:

    void on_do_button_clicked();
    void on_open_template_image_clicked();
    void on_open_image_clicked();

private:
    Ui::Form * ui;
    OpenCVImageItem * rootItem_;
    QImage template_image_;
    QGraphicsPixmapItem * template_image_show_=nullptr;
    void _p_update_template_image_show_();
};

#endif // CONTROLITEM_HPP
