#undef MACRO_PROTECTED
#define MACRO_PROTECTED public
#include "../OpenCVImageItem.hpp"
#include "../OpenCVUtility.hpp"
#include <QtGui/qpainter.h>
#include <QtGui/qpixmap.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qgraphicsview.h>
#include <QtCore/qdebug.h>
#include <private/qimage_p.h>
#include <algorithm>

namespace {
namespace __private {

QSize gen_best_draw_size(
    const QSizeF &s,
    const QSizeF &i
    ) {
    QSize ans{ 1,1 };

    if (i.width()==i.height()) {
        auto value_min=std::max(1,qRound(std::min(s.width(),s.height())));
        return{value_min,value_min};
    }

    auto source_=i.width()/i.height();
    auto target_=s.width()/s.height();

    if (source_<=target_) {
        /*调整宽*/
        ans.setHeight(std::max(qRound(s.height()),1));
        ans.setWidth(std::max(1,qRound(i.width()/i.height()*s.height())));
    }
    else {
        /*调整高*/
        ans.setWidth(std::max(1,qRound(s.width())));
        ans.setHeight(std::max(1,qRound(i.height()/i.width()*s.width())));
    }

    return ans;
}

class Item : public QGraphicsWidget {
    OpenCVImageItem * const super;
    std::shared_ptr<QPixmap> about_to_draw_resize_map_;
public:
    Item(OpenCVImageItem * s):QGraphicsWidget(s),super(s) {
        setAutoFillBackground(true);
        connect(super,&OpenCVImageItem::imageChanged,
            this,[this]() {about_to_draw_resize_map_.reset(); });
    }
    ~Item() {}

    void paint(
        QPainter * p,
        const QStyleOptionGraphicsItem *,
        QWidget *) {

        const QSizeF i_size=super->image().size();
        if (i_size.width()<=0) { return; }
        if (i_size.height()<=0) { return; }

        if (super->isAutoFitImageSize()) {
            const QImage & s_image=super->image();
            auto s_size=super->size();
            if ((s_image.width()<=s_size.width())&&
                (s_image.height()<=s_size.height())
                ) {
                about_to_draw_resize_map_.reset();
                this->setPos(
                    (s_size.width()-s_image.width())/2.0,
                    (s_size.height()-s_image.height())/2.0
                    );
                p->drawImage(0,0,super->image());
            }
            else {
                /*计算绘图大小*/
                auto s_size=super->size();
                auto b_size=gen_best_draw_size(s_size,i_size);

                if (bool(about_to_draw_resize_map_)&&
                    about_to_draw_resize_map_->size()==b_size
                    ) {
                    this->setPos(
                        (s_size.width()-b_size.width())/2.0,
                        (s_size.height()-b_size.height())/2.0
                        );
                    p->drawPixmap(0,0,*about_to_draw_resize_map_);
                }
                else {
                    about_to_draw_resize_map_=std::make_shared<QPixmap>(
                    QPixmap::fromImage(super->image().scaled(
                        b_size,Qt::IgnoreAspectRatio,
                        Qt::SmoothTransformation)));
                    b_size=about_to_draw_resize_map_->size();
                    this->setPos(
                        (s_size.width()-b_size.width())/2.0,
                        (s_size.height()-b_size.height())/2.0
                        );
                    p->drawPixmap(0,0,*about_to_draw_resize_map_);
                }
            }
        }
        else {
            /*直接绘制*/
            p->drawImage(0,0,super->image());
            about_to_draw_resize_map_.reset();
        }
    }

};

}
}

OpenCVImageItem::OpenCVImageItem(QGraphicsItem *parent)
    :P(parent) {
    bits_.reset();
    setAutoFitImageSize(true);
    item_=new __private::Item(this);
    item_->setZValue(-999);
    this->setFlag(OpenCVImageItem::ItemClipsChildrenToShape,true);
    {/*style*/
        QPalette pal=this->palette();
        pal.setColor(
            QPalette::Background,
            Qt::transparent
            );
        this->setPalette(pal);
    }
}

void OpenCVImageItem::paint(
        QPainter * a,
        const QStyleOptionGraphicsItem * b,
        QWidget * c) {
    QGraphicsWidget::paint(a,b,c);
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
        this->setMinimumWidth(std::max(128,image_.width()/112));
        this->setMinimumHeight(std::max(128,image_.height()/112));
        this->resize(width_,height_);
        if (item_) {
            item_->resize(image_.width(),image_.height());
            item_->setMinimumWidth(std::max(image_.width()/112,1));
            item_->setMinimumHeight(std::max(image_.height()/112,1));
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

void OpenCVImageItem::setAutoFitImageSize(bool v) {
    if (v==isAutoFitImageSize()) { return; }
    _setBit(Image_Auto_Fit_Size,v);
    if (v&&bool(item_)) { item_->setPos(0,0); }
    update();
}
