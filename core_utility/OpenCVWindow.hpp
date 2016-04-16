#ifndef OPENCVWINDOW_HPP
#define OPENCVWINDOW_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include <QtWidgets/qgraphicsview.h>
#include "core_utility_global.hpp"
#include "getxy.hpp"

class OpenCVHistItem;
class OpenCVImageItem;
class OpenCVChartImage;
class OpenCVScatterItem;
class OpenCVLineSeriesItem;
class OpenCVScene;
namespace cv{
class Mat;
}

class CORE_UTILITYSHARED_EXPORT OpenCVWindow : public QGraphicsView {
    Q_OBJECT
private:
    typedef QGraphicsView P;
    OpenCVScene * const scene_;
public:
    explicit OpenCVWindow(QWidget * parent=nullptr);
    virtual ~OpenCVWindow();

    template<typename B,typename E>OpenCVHistItem * insertHist(B,E);
    template<typename B,typename E>OpenCVScatterItem * insertScatter(B,E);
    template<typename B,typename E>OpenCVLineSeriesItem * insertLineSeries(B,E);
    virtual OpenCVHistItem * insertHist(QList<qreal> );
    virtual OpenCVImageItem * insertImage(QImage );
    OpenCVImageItem * insertImage(const cv::Mat&)/*call inertImage(QImage)*/;
    OpenCVImageItem * insertImage(cv::Mat&&)/*call inertImage(QImage)*/;
    virtual OpenCVChartImage * insertChartImage(QImage );
    virtual OpenCVScatterItem * insertScatter(QList<QPointF> );
    virtual OpenCVLineSeriesItem * insertLineSeries(QList<QPointF> );
    template<typename _U_>OpenCVScatterItem * insertScatter(std::initializer_list<_U_> &&);
    template<typename _U_>OpenCVLineSeriesItem * insertLineSeries(std::initializer_list<_U_> &&);
    void setImageAlg(const std::shared_ptr<const std::function<QImage(const QImage &)>> &);
    virtual void saveAll();
protected:
    void resizeEvent(QResizeEvent *event) override;
};

template<typename B,typename E>
OpenCVHistItem * OpenCVWindow::insertHist(B b,E e) {
    QList<qreal> _v_data;
    for(;b!=e;++b){
        _v_data.push_back( static_cast<qreal>(*b) );
    }
    return insertHist(std::move(_v_data));
}

template<typename _U_>
OpenCVScatterItem * OpenCVWindow::insertScatter(std::initializer_list<_U_> && o) {
    return insertScatter(o.begin(),o.end());
}

template<typename _U_>OpenCVLineSeriesItem *
OpenCVWindow::insertLineSeries(std::initializer_list<_U_> && o) {
    return insertLineSeries(o.begin(),o.end());
}

template<typename B,typename E>
OpenCVScatterItem * OpenCVWindow::insertScatter(B b,E e) {
    QList<QPointF> data_;
    for (;b!=e;++b) {
        data_.push_back({ getX(b) ,getY(b)});
    }
    return insertScatter(std::move(data_));
}

template<typename B,typename E>
OpenCVLineSeriesItem * OpenCVWindow::insertLineSeries(B b,E e) {
    QList<QPointF> data_;
    for (;b!=e;++b) {
        data_.push_back({ getX(b) ,getY(b)});
    }
    return insertLineSeries(std::move(data_));
}

#endif // OPENCVWINDOW_HPP
