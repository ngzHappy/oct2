#ifndef CONTROLITEM_HPP
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
        double dp;
        double minDist;
        double param1;
        double param2;
        int minRadius;
        int maxRadius;
        int method;
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
    std::shared_ptr<Pack> lastPack_;
};

inline bool operator==(
    const ControlItem::Pack & l,
    const ControlItem::Pack & r) {
    if (l.dp==r.dp)if (l.maxRadius==r.maxRadius)
        if (l.method==r.method)if (l.minDist==r.minDist)
            if (l.minRadius==r.minRadius)if (l.param1==r.param1)
                if (l.param2==r.param2)return true;
    return false;
}

#endif // CONTROLITEM_HPP
