#ifndef CONTROLITEM_HPP
#define CONTROLITEM_HPP

#include <QtWidgets/QWidget>
#include <memory>
class OpenCVImageItem;

namespace Ui {
class ControlItem;
}

class ControlItem : public QWidget {
    Q_OBJECT

public:

    class Pack {
    public:
        double l,a,b;
        double lBase,aBase,bBase;

        template<unsigned int N>double value()const;
        template<unsigned int N>double base()const;
    };

    ControlItem(OpenCVImageItem *,QWidget *parent=0);
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
    if (l.a==r.a)if (l.aBase==r.aBase)
        if (l.b==r.b)if (l.bBase==r.bBase)
            if (l.l==r.l)if (l.lBase==r.lBase) { return true; }
    return false;
}

namespace __ControlItem {
namespace __Pack{
namespace __private {
template<unsigned int N>class Get;
template<>class Get<0>{public:static double get(const ControlItem::Pack * p){return p->l;}};
template<>class Get<1>{public:static double get(const ControlItem::Pack * p){return p->a;}};
template<>class Get<2>{public:static double get(const ControlItem::Pack * p){return p->b;}};
}}}

namespace __ControlItem {
namespace __Base{
namespace __Pack{
namespace __private {
template<unsigned int N>class Get;
template<>class Get<0>{public:static double get(const ControlItem::Pack * p){return p->lBase;}};
template<>class Get<1>{public:static double get(const ControlItem::Pack * p){return p->aBase;}};
template<>class Get<2>{public:static double get(const ControlItem::Pack * p){return p->bBase;}};
}}}}

template<unsigned int N>double ControlItem::Pack::value()const{
    static_assert(N<3,"N just be 0,1,2");
    return __ControlItem::__Pack::__private::Get<N>::get(this);
}

template<unsigned int N>double ControlItem::Pack::base()const{
    static_assert(N<3,"N just be 0,1,2");
    return __ControlItem::__Base::__Pack::__private::Get<N>::get(this);
}

#endif // CONTROLITEM_HPP
