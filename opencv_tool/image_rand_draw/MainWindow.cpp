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

namespace {
namespace __private {

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
    const auto half_image_width_=input_image_width_/2;
    const auto half_image_height_=input_image_height_/2;

    struct DrawMatrix :public QMatrix {
        std::size_t id=0;
    };
    std::list<DrawMatrix> rotate_rects;

    QPointF point_0(half_image_width_,half_image_height_);
    QPointF point_1(half_image_width_+input_image_width_,half_image_height_);
    QPointF point_2(half_image_width_+input_image_width_,half_image_height_+input_image_height_);
    QPointF point_3(half_image_width_,half_image_height_+input_image_height_);
    QRectF image_rect_(0,0,image_width_,image_height_);

    auto rand_function1=[]() {return (rand()%13482)/13482.0+.5; };
    auto rand_function2=[]() {return (rand()%13482)/13482.0+.6; };

    auto gen_matrix_1=[&]() {
        const auto half_image_width_=input_image_width_;
        const auto half_image_height_=input_image_height_;
        double scale_=(rand()%2)?rand_function1():rand_function2();

        DrawMatrix matrix;

        matrix.translate(
            half_image_width_+(rand()%(half_image_width_/2)),
            half_image_height_+(rand()%(half_image_height_/2)));
        matrix.rotate((rand()%360)+180);
        matrix.translate(
            (rand()%(half_image_width_/35)),
            (rand()%(half_image_height_/35)));
        matrix.rotate((rand()%360)+180);
        matrix.scale(scale_,scale_);

        auto _point_0=point_0*matrix;
        auto _point_1=point_1*matrix;
        auto _point_2=point_2*matrix;
        auto _point_3=point_3*matrix;

        if (
            image_rect_.contains(_point_0)&&
            image_rect_.contains(_point_2)&&
            image_rect_.contains(_point_1)&&
            image_rect_.contains(_point_3)
            ) {
            matrix.id=rotate_rects.size();
            rotate_rects.push_back(matrix);
        }
    };

    auto gen_matrix_2=[&]() {
        double scale_=(rand()%2)?rand_function1():rand_function2();

        DrawMatrix matrix;

        matrix.translate(
            half_image_width_+(rand()%(half_image_width_/2)),
            half_image_height_+(rand()%(half_image_height_/2)));
        matrix.rotate((rand()%360)+180);
        matrix.scale(scale_,scale_);

        auto _point_0=point_0*matrix;
        auto _point_1=point_1*matrix;
        auto _point_2=point_2*matrix;
        auto _point_3=point_3*matrix;

        if (
            image_rect_.contains(_point_0)&&
            image_rect_.contains(_point_2)&&
            image_rect_.contains(_point_1)&&
            image_rect_.contains(_point_3)
            ) {
            matrix.id=rotate_rects.size();
            rotate_rects.push_back(matrix);
        }
    };

    //cv::INTERSECT_FULL
    for (int i=0; (i<9000)&&(rotate_rects.size()<360); ++i) {
        if (rand()&1) {
            gen_matrix_2();
            gen_matrix_1();
        }
        else { gen_matrix_1(); }
    }

    if (rotate_rects.empty()) { return; }
    const QPointF drawPos(0,0);

    auto runFuncion=[&](DrawMatrix & i) ->void {
        QImage _image_(
            image_width_,
            image_height_,
            image_.format()
            );
        _image_.fill(QColor(0,0,0));
        QPainter painter(&_image_);

        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
        painter.setMatrix(i);

        painter.drawImage(drawPos,image_);
        _image_.save(dir_.absoluteFilePath(
            QString("%1").arg(i.id,6,10,QChar('0')))+".png");
    };

    QtConcurrent::blockingMap(
        rotate_rects.begin(),
        rotate_rects.end(),
        runFuncion
        );

}

}
}

void MainWindow::select() {

}

void MainWindow::save() {

    __private::make_rand_image(image_,to_dir_);
}

MainWindow::MainWindow(QWidget *parent)
    : P(parent) {
    
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
    to_dir_=std::forward<_t_DSTDIR_t__>(_dstDir_);
}

void MainWindow::setDstDir(const QString&_dstDir_) {
    _p_setDstDir(_dstDir_);
}

void MainWindow::setDstDir(QString&&_dstDir_) {
    _p_setDstDir(std::move(_dstDir_));
}

static void _on_start_up() {
    std::srand(std::rand()+int(std::time(nullptr)));
}

Q_COREAPP_STARTUP_FUNCTION(_on_start_up)

