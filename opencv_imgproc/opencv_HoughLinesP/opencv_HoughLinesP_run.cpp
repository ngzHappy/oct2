/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_HoughLinesP_run_exception.cpp"
#include "OpenCVWindowDetail.hpp"
#include "ControlItem.hpp"
#include <QtWidgets/qfiledialog.h>
#include <functional>
#include <QtGui/qpainter.h>
//#include <QtCharts>

OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i){
    auto * ans = OpenCVWindow::insertImage(i);
    auto * var_item =new OpenCVVerticalItems(ans);
    var_item->addWidget(new ControlItem(ans));
    ans->resize(
                i.width()+300,
                i.height()+300
                );
    return ans;
}

void ControlItem::on_do_button_clicked(){
    std::shared_ptr<ControlItem::Pack> pack=
            std::make_shared<ControlItem::Pack>();
    _p_init_pack(pack.get());

    typedef std::function<QImage(const QImage &)> FunctionType;
    auto function=std::shared_ptr<FunctionType>(
        new FunctionType([pack](const QImage & inputImage)->QImage {
        try {
            cv::Mat image=OpenCVUtility::tryRead(inputImage);
            std::vector<cv::Vec4i> lines;
            cv::HoughLinesP(
                image,
                lines,
                pack->rho,
                pack->theta,
                pack->threshold,
                pack->minLineLength,
                pack->maxLineGap);

            QImage image_ans=inputImage;
            image_ans=image_ans.convertToFormat(QImage::Format_RGBA8888);
            QPainter painter(&image_ans);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setRenderHint(QPainter::SmoothPixmapTransform);
            painter.setRenderHint(QPainter::TextAntialiasing);
            painter.setRenderHint(QPainter::HighQualityAntialiasing);
            for (const auto & i:lines) {
                painter.setPen(QPen(QColor(255,std::rand()&127,std::rand()&127),2));
                painter.drawLine(i[0],i[1],i[2],i[3]);
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

void ControlItem::on_select_image_button_clicked(){
    QString fileName = QFileDialog::getOpenFileName();
    if(fileName.isEmpty()){return;}
    QImage image_(fileName);
    image_=image_.convertToFormat(QImage::Format_Grayscale8);
    rootItem_->setImage(std::move(image_));
}

namespace opencv_HoughLinesP {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {
        window->insertImage(
                    QImage(image_name).convertToFormat(QImage::Format_Grayscale8))
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

