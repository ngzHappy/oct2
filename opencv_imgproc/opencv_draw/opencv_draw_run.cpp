/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include "private/opencv_draw_run_exception.cpp"

static inline void openCVPaintTest(QImage image,OpenCVWindow * window)try{
    auto matImage = OpenCVUtility::tryRead(image);

    {
        /*绘制箭头曲线*/
        cv::arrowedLine(
            matImage,{ 100,200 },{ 130,230 },
            cv::Scalar(255,255,255,155),
            1,
            cv::LineTypes::LINE_8
            );
    }

    {
        cv::rectangle(
            matImage,
            cv::Rect(0,0,image.width(),image.height()),
            cv::Scalar(200,200,200,100),
            16
            );
    }

    {
        cv::putText(
            matImage,
            u8"蒙娜丽莎的微笑",
            {100,100},
            cv::FONT_HERSHEY_SIMPLEX,1,
            {255,255,255}
        );
    }

    {
        cv::ellipse(
            matImage,
            {cv::Point2f(300,100),cv::Size(100,100),0},
            cv::Scalar(200,200,200,100)
            );
    }

    window->insertImage( OpenCVUtility::tryRead(matImage) )
        ->setWindowTitle("OpenCV Paint");
}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

static inline void qtPaintTest(QImage image,OpenCVWindow * window){

    QPainter painter(&image);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    {
        /*绘制边框*/
        painter.setBrush(QColor(Qt::transparent));
        painter.setPen( QPen(QColor(200,200,200,100),16) );
        painter.drawRect(0,0,image.width(),image.height());
    }

    {
        /*保存状态*/
        painter.save();
        /*坐标变换*/
        painter.translate(100,100);
        painter.rotate(45);
        /*绘制文字*/
        QFont font=painter.font();
        font.setPixelSize(32);
        painter.setFont(font);
        painter.setBrush(QColor(255,255,255,100));
        painter.setPen( QPen(QColor(255,255,255,160),8) );
        painter.drawText(0,0,QObject::trUtf8(u8"蒙娜丽莎的微笑"));
        /*恢复状态*/
        painter.restore();
    }

    {
        auto makeArrayTriangle=[](
            const QPointF & start_,
            const QPointF & end_,
            float arrayWeight_=6,
            const float arrayLength_=12
            ) ->QPainterPath{
            QPainterPath path;
            if (arrayLength_==0) { return path; }
            if (arrayWeight_==0) { return path; }
            if (start_==end_) { return path; }
            arrayWeight_/=2;
            auto dx_=end_.x()-start_.x();/*单位方向向量dx*/
            auto dy_=end_.y()-start_.y();/*单位方向向量dy*/
            const auto len_=std::sqrt(dx_*dx_+dy_*dy_);/*线段长*/
            if (len_==0) { return path; }
            {dx_/=len_; dy_/=len_; }
            {
                /*计算三角形*/
                {   /*在法线方向上找到两个点*/
                    QPointF normal_(-dy_,dx_);
                    normal_*=arrayWeight_;
                    path.moveTo(normal_+end_);
                    path.lineTo(end_-normal_);
                }
                {   /*在方向向量上找到一个点*/
                    QPointF array_(dx_,dy_);
                    path.lineTo(array_*arrayLength_+end_);
                }
                /*闭合曲线*/
                path.closeSubpath();
            }
            return path;
        };

        {
            painter.setBrush(QColor(255,255,255,160));
            const QPointF p0(100,200),p1(130,230);
            painter.setPen( QPen(QColor(255,255,255,0),0) );
            painter.drawPath(makeArrayTriangle(p0,p1))/*绘制箭头三角形*/;
            painter.setPen( QPen(QColor(255,255,255,160),2) );
            painter.drawLine(p0,p1)/*绘制直线*/;
        }

    }

    {
        painter.setPen(QPen(QColor(0,0,0,0),0));
        QPointF cen_(300, 100);
        float r=50;
        QRadialGradient radialGrad(cen_,r);
        radialGrad.setColorAt(0, QColor(200,200,200,200));
        radialGrad.setColorAt(0.5,QColor(200,200,200,180));
        radialGrad.setColorAt(1, QColor(200,200,200,10));
        painter.setBrush(radialGrad);
        painter.drawEllipse(cen_,r,r);
    }

    window->insertImage(image)
        ->setWindowTitle("Qt Paint");
}


extern void run(OpenCVWindow * window) {

    QImage image("images:000006");
    window->insertImage(image)->setWindowTitle(QObject::trUtf8(u8"原始图像"));
    qtPaintTest(image,window);
    openCVPaintTest(image,window);

}

