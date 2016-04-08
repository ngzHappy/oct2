#include "../OpenCVImageItem.hpp"
#include "../OpenCVUtility.hpp"
#include <QtGui/qpainter.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qgraphicsview.h>
#include <QtCore/qdebug.h>
#include <private/qimage_p.h>
#include <algorithm>

namespace {
namespace __private {

class Item : public QGraphicsWidget {
    OpenCVImageItem * const super;
public:
    Item(OpenCVImageItem * s):QGraphicsWidget(s),super(s) {}
    ~Item() {}
    void paint(
        QPainter * p,
        const QStyleOptionGraphicsItem *,
        QWidget *) {
        p->drawImage(0,0,super->image());
    }

};

}
}

OpenCVImageItem::OpenCVImageItem(QGraphicsItem *parent)
    :P(parent) {
    item_=new __private::Item(this);
    this->setFlag(OpenCVImageItem::ItemClipsChildrenToShape,true);
}

void OpenCVImageItem::paint(
        QPainter *,
        const QStyleOptionGraphicsItem *,
        QWidget *) {

}

void OpenCVImageItem::setAlgFunction(AlgFunctionType alg__) {
    alg_=std::move(alg__);

    if (alg_) {
        auto & fun_=*alg_;
        if (fun_) {
            image_=fun_(image_input_);
            _tryResize();
            imageChanged();
            update();
            return;
        }
    }

    {
        image_=image_input_;
        _tryResize();
        imageChanged();
        update();
        return;
    }

}

OpenCVImageItem::~OpenCVImageItem() {
    if (item_) { item_->deleteLater(); }
}

void OpenCVImageItem::renderTo(QImage & i) { i=image_; }

void OpenCVImageItem::saveImage() {

    {
        const QGraphicsScene * sc__=this->scene();
        if (sc__==nullptr) { return; }
    }

    {
        const QString saveFileName_=
            QFileDialog::getSaveFileName(nullptr,
                trUtf8(u8"设置保存文件名"),
                QString(),
                u8"Images (*.png *.jpg)"_qs
                );
        if (saveFileName_.isEmpty()) { return; }
        image_.save(saveFileName_);
    }

}

void OpenCVImageItem::tryResizeImage() {
    {
        const auto size_=this->size();
        const auto width_=(std::max<qreal>)(
        { 128.0,static_cast<qreal>(image_.width()),size_.width() });
        const auto height_=(std::max<qreal>)(
        { 128.0,static_cast<qreal>(image_.height()),size_.height() });
        this->setMinimumWidth(std::max(128,image_.width()));
        this->setMinimumHeight(std::max(128,image_.height()));
        this->resize(width_,height_);
        if (item_) {
            item_->resize(image_.width(),image_.height());
            item_->setMinimumWidth(image_.width());
            item_->setMinimumHeight(image_.height());
        }
    }
}

void OpenCVImageItem::_tryResize() {
    tryResizeImage();
}

void OpenCVImageItem::setImage(QImage i) {
    image_input_=std::move(i);
    _p_private__set_image();
    image_=image_input_;

    if (alg_) {
        auto & fun_=*alg_;
        if (fun_) { image_=fun_(image_input_); }
    }

    _tryResize();
    imageChanged();
    update();
}

void OpenCVImageItem::_p_private__set_image() {
    {
        QImageData * ptr_=image_input_.data_ptr();
        if ((ptr_)&&(ptr_->cleanupFunction)) {
            bool need_copy_=true;
            if (ptr_->cleanupFunction==OpenCVUtility::getHandleQImage()) {
                if (ptr_->cleanupInfo) {
                    cv::Mat * mat_=reinterpret_cast<cv::Mat *>(ptr_->cleanupInfo);
                    if (mat_->u) {
                        need_copy_=false;/*此处已经完成是否拷贝的决策*/
                        if (mat_->u->refcount!=1) {
                            image_input_=image_input_.copy();
                        }
                    }
                }
            }
            if (need_copy_) { image_input_=image_input_.copy(); }
        }
        else {
            image_input_.detach();/*获得独立备份*/
        }
    }
}

