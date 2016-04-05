#ifndef OPENCVWINDOW_HPP
#define OPENCVWINDOW_HPP() 1

#include <QtWidgets/qgraphicsview.h>
#include "OpenCVScene.hpp"
#include "core_utility_global.hpp"
#include "getxy.hpp"

class CORE_UTILITYSHARED_EXPORT OpenCVWindow : public QGraphicsView {
    Q_OBJECT
private:
    typedef QGraphicsView P;
    OpenCVScene * const scene_;
public:
    explicit OpenCVWindow(QWidget * parent=nullptr);
    virtual ~OpenCVWindow();

    template<typename B,typename E>
    OpenCVHistItem * insertHist(B,E);
    template<typename B,typename E>
    OpenCVScatterItem * insertScatter(B,E);
    OpenCVHistItem * insertHist(QList<qreal> data_) { return scene_->insertHist(std::move(data_)); }
    virtual OpenCVImageItem * insertImage(QImage i) { return scene_->insertImage(std::move(i)); }
    OpenCVScatterItem * insertScatter(QList<QPointF> data_) { return scene_->insertScatter(std::move(data_)); }
    void setImageAlg(const OpenCVImageItem::AlgFunctionType &);
protected:
    void resizeEvent(QResizeEvent *event) override;
};

template<typename B,typename E>
OpenCVHistItem * OpenCVWindow::insertHist(B b,E e) {
    return scene_->insertHist<B,E>(b,e);
}

template<typename B,typename E>
OpenCVScatterItem * OpenCVWindow::insertScatter(B b,E e) {
    QList<QPointF> data_;
    for (;b!=e;++b) {
        data_.push_back({ getX(b) ,getY(b)});
    }
    return insertScatter(std::move(data_));
}

#endif // OPENCVWINDOW_HPP
