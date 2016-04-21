/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_HoughLines_run_exception.cpp"
#include "OpenCVWindowDetail.hpp"
#include "ControlItem.hpp"
#include <QtWidgets/qfiledialog.h>
//#include <QtCharts>

OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i){
    auto ans=OpenCVWindow::insertImage(i);
    auto item=new OpenCVVerticalItems(ans);
    item->addWidget(new ControlItem(ans),true);
    ans->resize(
        i.width()+300,
        i.height()+300
    );
    return ans;
}

void ControlItem::on_select_image_button_clicked(){
    QString fileName = QFileDialog::getOpenFileName();
    if(fileName.isEmpty()){return;}
    QImage image_(fileName);
    image_=image_.convertToFormat(QImage::Format_Grayscale8);
    rootItem_->setImage(std::move(image_));
}

void ControlItem::on_do_button_clicked(){
    std::shared_ptr<ControlItem::Pack> pack=
            std::make_shared<ControlItem::Pack>();
    _p_init_pack(pack.get());

    typedef std::function<QImage(const QImage &)> FunctionType;
    auto function=std::shared_ptr<FunctionType>(
        new FunctionType([pack](const QImage & inputImage)->QImage {
        if (inputImage.isNull()) { return{}; }
        try {
            cv::Mat image=OpenCVUtility::tryRead(inputImage);
            std::vector<cv::Vec2f> lines;
            cv::HoughLines(
                image,
                lines,
                pack->rho,
                pack->theta,
                pack->threshold,
                pack->srn,
                pack->stn,
                pack->min_theta,
                pack->max_theta);

            QImage image_ans=inputImage;
            if (lines.size()>0) {
                auto color_step=std::max(255/int(lines.size()),1);
                image_ans=image_ans.convertToFormat(QImage::Format_RGBA8888);
                QPainter painter(&image_ans);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.setRenderHint(QPainter::SmoothPixmapTransform);
                painter.setRenderHint(QPainter::TextAntialiasing);
                painter.setRenderHint(QPainter::HighQualityAntialiasing);
                double image_length=2*std::max(inputImage.width(),inputImage.height());
                auto _color=0;
                for (const auto & i:lines) {
                    painter.setPen(QPen(QColor(_color,255,std::rand()&127),2));
                    _color+=color_step;
                    if (_color>255) { _color=std::rand()&63; }
                    painter.save();
                    painter.rotate((i[1])/3.1415926454*180);
                    painter.translate(i[0],0);
                    painter.drawLine(0,-image_length,0,image_length);
                    painter.restore();
                }
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

namespace opencv_HoughLines{
extern void run(OpenCVWindow * window) try{

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

