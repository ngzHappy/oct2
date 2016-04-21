#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

#include <QtWidgets/QWidget>
#include <memory>
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
        double h,l,s;
        double hBase,lBase,sBase;
    };

    ControlItem(OpenCVImageItem *,QWidget *parent = 0);
    ~ControlItem();

private slots:
    void on_select_image_button_clicked();

    void on_do_button_clicked();

private:
    Ui::ControlItem *ui;
    OpenCVImageItem * rootItem_;
    void _p_init_pack(Pack *);
    std::shared_ptr<Pack> lastPack_;
};

inline bool operator==(
    const ControlItem::Pack & l,
    const ControlItem::Pack & r
    ) {
    return false;
}

#endif // CONTROLITEM_HPP
