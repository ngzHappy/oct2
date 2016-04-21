/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_HoughCircles_run_exception.cpp"
#include "OpenCVWindowDetail.hpp"
#include <QtWidgets/qfiledialog.h>
#include "ControlItem.hpp"
//#include <QtCharts>

OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i) {
    i=i.convertToFormat(QImage::Format_Grayscale8);
    auto ans= OpenCVWindow::insertImage(i);
    auto item = new OpenCVVerticalItems(ans);
    item->addWidget(new ControlItem(ans),true);
    ans->resize(
        i.width()+300,
        i.height()+300);
    return ans;
}

void ControlItem::on_select_image_button_clicked(){
    QString fileName = QFileDialog::getOpenFileName();
    if(fileName.isEmpty()){return;}
    QImage image_(fileName);
    image_=image_.convertToFormat(QImage::Format_Grayscale8);
    rootItem_->setImage(std::move(image_));
}

void ControlItem::on_do_button_clicked() {
    std::shared_ptr<ControlItem::Pack> pack=
        std::make_shared<ControlItem::Pack>();
    _p_init_pack(pack.get());

    if (bool(lastPack_)&&(*lastPack_==*pack)) {
        return;
    }
    lastPack_=pack;

    typedef std::function<QImage(const QImage &)> FunctionType;
    auto function=std::shared_ptr<FunctionType>(
        new FunctionType([pack](const QImage & inputImage)->QImage {
        try {
            cv::Mat image=OpenCVUtility::tryRead(inputImage);
            std::vector<cv::Vec3f> circles;
            cv::HoughCircles(
                image,
                circles,
                pack->method,
                pack->dp,
                pack->minDist,
                pack->param1,
                pack->param2,
                pack->minRadius,
                pack->maxRadius);

            QImage image_ans=inputImage;
            image_ans=image_ans.convertToFormat(QImage::Format_RGBA8888);
            QPainter painter(&image_ans);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setRenderHint(QPainter::SmoothPixmapTransform);
            painter.setRenderHint(QPainter::TextAntialiasing);
            painter.setRenderHint(QPainter::HighQualityAntialiasing);
            for (const auto & i:circles) {
                painter.setPen(QPen(QColor(255,std::rand()&127,std::rand()&127),2));
                painter.drawEllipse(QPointF(i[0],i[1]),i[2],i[2]);
            }
            return std::move(image_ans);
        }
        catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
            return inputImage;
        }
    }));

    rootItem_->setAlgFunction(function);
}


namespace opencv_HoughCircles {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        window->insertImage(QImage(image_name))
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

