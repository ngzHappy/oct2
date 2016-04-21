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
    std::shared_ptr<Pack> lastPack_;
};

inline bool operator==(
    const ControlItem::Pack &l,
    const ControlItem::Pack &r
    ){
    if (l.max_theta==r.max_theta)if (l.min_theta==r.min_theta)
        if (l.rho==r.rho)if (l.srn==r.srn)if (l.stn==r.stn)
            if (l.theta==r.theta)if (l.threshold==r.threshold)return true;
    return false;
}

#endif // CONTROLITEM_HPP
