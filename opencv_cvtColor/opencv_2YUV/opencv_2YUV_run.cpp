﻿/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_2YUV_run_exception.cpp"
#include "ControlItem.hpp"
#include "OpenCVWindowDetail.hpp"
#include <QtWidgets/qfiledialog.h>
//#include <QtCharts>
OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i){
    auto ans=OpenCVWindow::insertImage(
        i.convertToFormat(QImage::Format_RGBA8888));
    auto item=new OpenCVVerticalItems(ans);
    item->addWidget(new ControlItem(ans),true);
    ans->resize(768,600);
    return ans;
}

void ControlItem::on_select_image_button_clicked(){
    QString fileName = QFileDialog::getOpenFileName();
    if(fileName.isEmpty()){return;}
    QImage image_(fileName);
    rootItem_->setImage(std::move(image_));
}

void ControlItem::on_do_button_clicked(){
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
        if (inputImage.isNull()) { return{}; }
        try {
            cv::Mat image=OpenCVUtility::tryRead(
                inputImage.convertToFormat(QImage::Format_RGBA8888)
            );
           
            std::vector<cv::Mat> yuv;
            cv::Mat rgba_a;
            {
                cv::split(image,yuv);
                rgba_a=yuv[3];
                yuv.resize(3);
            }

            cv::merge(yuv,image);
            yuv.clear();

            cv::cvtColor(image,image,cv::COLOR_RGB2Luv);
            cv::split(image,yuv);

            if (pack->value<0>()!=1) { yuv[0]*=pack->value<0>(); }
            if (pack->value<1>()!=1) { yuv[1]*=pack->value<1>(); }
            if (pack->value<2>()!=1) { yuv[2]*=pack->value<2>(); }

            if (pack->base<0>()!=0) { yuv[0]+=pack->base<0>(); }
            if (pack->base<1>()!=0) { yuv[1]+=pack->base<1>(); }
            if (pack->base<2>()!=0) { yuv[2]+=pack->base<2>(); }

            cv::merge(yuv,image);
            cv::cvtColor(image,image,cv::COLOR_Luv2RGB);

            cv::split(image,yuv);
            yuv.push_back(rgba_a);
            cv::merge(yuv,image);

            rgba_a.release();
            yuv.clear();

            return OpenCVUtility::tryRead(image);
        }
        catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
            return inputImage;
        }
    }));

    rootItem_->setAlgFunction(function);
}

namespace opencv_2YUV{
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

