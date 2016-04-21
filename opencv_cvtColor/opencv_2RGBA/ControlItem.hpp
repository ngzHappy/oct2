#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

#include <memory>
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
        double r,g,b,a;
        double rBase,gBase,bBase,aBase;
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
    const ControlItem::Pack & r) {
    if (l.a!=r.a) { return false; }
    if (l.aBase!=r.aBase) { return false; }
    if (l.b!=r.b) { return false; }
    if (l.bBase!=r.bBase) { return false; }
    if (l.g!=r.g) { return false; }
    if (l.gBase!=r.gBase) { return false; }
    if (l.r!=r.r) { return false; }
    return l.rBase==r.rBase;
}

#endif // CONTROLITEM_HPP
