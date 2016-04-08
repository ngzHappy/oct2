#ifndef xOPENCVIMAGEITEM_HPP
#define xOPENCVIMAGEITEM_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include <functional>
#include <memory>
#include <QtGui/qimage.h>
#include "OpenCVItem.hpp"

class CORE_UTILITYSHARED_EXPORT OpenCVImageItem : public OpenCVItem {
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
public:
    typedef std::shared_ptr< const std::function< QImage(const QImage &) > >  AlgFunctionType;
private:
    typedef OpenCVItem P;
    QPointer<QGraphicsWidget> item_;
    QImage image_;
    QImage image_input_;
    AlgFunctionType alg_;
public:
    OpenCVImageItem(QGraphicsItem *parent=nullptr);
    virtual ~OpenCVImageItem();

    const QImage & image()const { return image_; }
    void setImage(QImage);

    QGraphicsWidget * getImageItem() const { return item_.data(); }
    const AlgFunctionType & getAlgFunction()const { return alg_; }
    void setAlgFunction(AlgFunctionType);
    void renderTo(QImage &) override;
    virtual void saveImage();
    virtual void tryResizeImage();
signals:
    void imageChanged();
protected:
    void _tryResize();
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
private:
    void _p_private__set_image();
};

#endif // OPENCVIMAGEITEM_HPP
