#include "MainWindow.hpp"
#include <QtGui/qpainter.h>
#include <QtCore/qdir.h>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <list>
#include <array>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/qapplication.h>
#include <QtQuick/QtQuick>
#include <QtWidgets/qfiledialog.h>
#include <opencv2/opencv.hpp>
#include <iostream>

namespace {
namespace __private {

class DrawMatrix :public QMatrix {
public:
    std::int32_t id=0;
    using QMatrix::QMatrix;
    DrawMatrix() {}
    DrawMatrix(QMatrix  && t):QMatrix(std::move(t)) {}
    DrawMatrix(const QMatrix  & t):QMatrix(t) {}
};

/*进行逻辑坐标变换*/
std::list<DrawMatrix> gen_rotate_matrix() {
    std::list<DrawMatrix> ans;

    for (int i=0; i<360;++i) {
        float scale_=((rand()%200)/200.0f)+0.32f;
        DrawMatrix matrix;
        matrix.rotate(rand()%360+((rand()%200)/200.0f));
        matrix.scale(scale_,scale_);
        matrix.id=(ans.size()+1);
        ans.push_back(matrix);
    }
    return std::move(ans);
}

void make_rand_image(
        const QImage & image_,
        QString build_path_
        ) {

    QDir dir_(build_path_);

    const auto input_image_width_=image_.width();
    const auto input_image_height_=image_.height();
    if (input_image_width_<=0) { return; }
    if (input_image_height_<=0) { return; }
    const auto image_width_=input_image_width_*2;
    const auto image_height_=input_image_height_*2;

    std::list<DrawMatrix> rotate_rects=gen_rotate_matrix();

    {
        QMatrix matrix_base;
        rotate_rects.push_back(matrix_base);
    }

    class DrawPack {
    public:
        const QImage image_;
        const QDir dir_;
        std::int32_t image_width_;
        std::int32_t image_height_;
    };

    std::shared_ptr<const DrawPack> pack=std::shared_ptr<const DrawPack>{
        new DrawPack{image_,dir_,image_width_,image_height_}
    };

    auto runFuncion=[pack](DrawMatrix & i) ->void {

        auto to_cvPoint=[](const auto & v) {return cv::Point2f(v.x(),v.y());};

        std::vector<cv::Point2f> points{
            to_cvPoint(QPointF(0,0)*i),
            to_cvPoint(QPointF(0,pack->image_height_/2)*i),
            to_cvPoint(QPointF(pack->image_width_/2,pack->image_height_/2)*i),
            to_cvPoint(QPointF(pack->image_width_/2,0)*i),
        };

        /*计算绘图坐标*/
        cv::Rect bound_rect=cv::boundingRect(points);

        /*生成边框*/
        auto ax=(rand()&15)+1;
        auto ay=(rand()&15)+1;

        QImage _image_(
            bound_rect.width+2*ax,
            bound_rect.height+2*ay,
            pack->image_.format()
        );

        /*计算逻辑坐标到绘图坐标*/
        QMatrix matrix;
        matrix.translate(
            ax-bound_rect.x,
            ay-bound_rect.y
            );

        _image_.fill(QColor(0,0,0,0));
        {
            QPainter painter(&_image_);

            painter.setRenderHint(QPainter::SmoothPixmapTransform);
            painter.setRenderHint(QPainter::HighQualityAntialiasing);
            painter.setMatrix(i*matrix/*将逻辑坐标投影到绘图坐标*/);
            const auto & image_=pack->image_;

            painter.drawImage(QPoint{ 0,0 },image_);

        }

        /*设置文件名并保存*/
        QString fileName=QString("%1").arg(i.id,6,10,QChar('0'));
        fileName=pack->dir_.absoluteFilePath(fileName+".png");
        _image_.save(fileName);

    };

    /*多线程执行任务*/
    QtConcurrent::blockingMap(
                rotate_rects.begin(),
                rotate_rects.end(),
                runFuncion
                );

}

}
}

void MainWindow::selectDir() {
    QString _dir_name_=QFileDialog::getExistingDirectory(nullptr,"");
    if (_dir_name_.isEmpty()) { return; }
    setDstDir(std::move(_dir_name_));
}

void MainWindow::selectImage() {
    QString _file_name_=QFileDialog::getOpenFileName(nullptr);
    if (_file_name_.isEmpty()) { return; }
    QImage _image_(_file_name_);
    if (_image_.width()<=0) { return; }
    if (_image_.height()<=0) { return; }
    setImage(std::move(_image_));
    QUrl _url_=QUrl::fromLocalFile(_file_name_);
    setImageQmlPath(_url_.toString());
}

void MainWindow::save() {
    __private::make_rand_image(image_,to_dir_);
}

MainWindow::MainWindow(QWindow *parent)
    : P(parent) {
    rootContext()->setContextProperty("rootWindow",this);
    setSource(QUrl("qrc:/qml/MainWindow.qml"));
    setResizeMode(MainWindow::ResizeMode::SizeRootObjectToView);
    this->setMinimumHeight(512);
    this->setMinimumWidth(512);
    this->resize(600,600);
    setImageQmlPath("qrc:/image/000006.jpg");
    setImage(QImage(":/image/000006.jpg"));


}

MainWindow::~MainWindow() {

}


const QImage & MainWindow::getImage() const {
    return image_;
}

template<typename _t_IMAGE_t__>
void MainWindow::_p_setImage(_t_IMAGE_t__ &&_image_) {
    image_=std::forward<_t_IMAGE_t__>(_image_);
}

void MainWindow::setImage(const QImage&_image_) {
    _p_setImage(_image_);
}

void MainWindow::setImage(QImage&&_image_) {
    _p_setImage(std::move(_image_));
}


const QString & MainWindow::getDstDir() const {
    return to_dir_;
}

template<typename _t_DSTDIR_t__>
void MainWindow::_p_setDstDir(_t_DSTDIR_t__ &&_dstDir_) {
    if (to_dir_==_dstDir_) { return; }
    to_dir_=std::forward<_t_DSTDIR_t__>(_dstDir_);
    dstDirChanged();
}

void MainWindow::setDstDir(const QString&_dstDir_) {
    _p_setDstDir(_dstDir_);
}

void MainWindow::setDstDir(QString&&_dstDir_) {
    _p_setDstDir(std::move(_dstDir_));
}

const QString & MainWindow::getImageQmlPath() const {
    return image_dir_name_;
}

template<typename _t_IMAGEQMLPATH_t__>
void MainWindow::_p_setImageQmlPath(_t_IMAGEQMLPATH_t__ &&_imageQmlPath_) {
    if (image_dir_name_==_imageQmlPath_) { return; }
    image_dir_name_=std::forward<_t_IMAGEQMLPATH_t__>(_imageQmlPath_);
    imageQmlPathChanged();
}

void MainWindow::setImageQmlPath(const QString&_imageQmlPath_) {
    _p_setImageQmlPath(_imageQmlPath_);
}

void MainWindow::setImageQmlPath(QString&&_imageQmlPath_) {
    _p_setImageQmlPath(std::move(_imageQmlPath_));
}

static void _on_start_up() {
    std::srand(std::rand()+int(std::time(nullptr)));
}
Q_COREAPP_STARTUP_FUNCTION(_on_start_up)

