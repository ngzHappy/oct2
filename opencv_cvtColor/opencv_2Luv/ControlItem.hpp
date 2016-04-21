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
        double l,u,v;
        double lBase,uBase,vBase;

        template<unsigned int N>double value()const;
        template<unsigned int N>double base()const;
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
    if (l.l==r.l)if (l.lBase==r.lBase)
        if (l.u==r.u)if (l.uBase==r.uBase)
            if (l.v==r.v)if (l.vBase==r.vBase)return true;
    return false;
}

namespace __private {
namespace __Pack{
namespace __ControlItem {

namespace __Base {
template<unsigned int N>class Get;
template<>class Get<0> { public:static double get(const ControlItem::Pack * i) { return i->lBase; } };
template<>class Get<1> {public:static double get(const ControlItem::Pack * i) { return i->uBase; }};
template<>class Get<2> {public:static double get(const ControlItem::Pack * i) { return i->vBase; }};
}

template<unsigned int N>class Get;
template<>class Get<0> { public:static double get(const ControlItem::Pack * i) { return i->l; } };
template<>class Get<1> {public:static double get(const ControlItem::Pack * i) { return i->u; }};
template<>class Get<2> {public:static double get(const ControlItem::Pack * i) { return i->v; }};

}}}

template<unsigned int N>double ControlItem::Pack::value()const {
    return __private::__Pack::__ControlItem::Get<N>::get(this);
}

template<unsigned int N>double ControlItem::Pack::base()const {
    return __private::__Pack::__ControlItem::__Base::Get<N>::get(this);
}

#endif // CONTROLITEM_HPP
