#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

#include <memory>
#include <QtWidgets/QWidget>
class OpenCVImageItem ;

namespace Ui {
class ControlItem;
}

class ControlItem : public QWidget
{
    Q_OBJECT

public:

    class Pack{
    public:
        int blockSize;
        int ksize;
        double k;
    };

    ControlItem(OpenCVImageItem *,QWidget *parent = 0);
    ~ControlItem();

private slots:
    void on_select_image_button_clicked();
    void on_do_button_clicked();

private:
    Ui::ControlItem *ui;
    void _p_init_pack(Pack *);
    OpenCVImageItem * rootItem_;
    std::shared_ptr<Pack> lastPack_;
};

inline bool operator ==(
        const ControlItem::Pack & l,
        const ControlItem::Pack & r){
    if(l.k==r.k)if(l.ksize==r.ksize)if(l.blockSize==r.blockSize)
        return true;
    return false;
}

#endif // CONTROLITEM_HPP
