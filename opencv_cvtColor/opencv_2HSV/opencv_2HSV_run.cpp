/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_2HSV_run_exception.cpp"
#include "ControlItem.hpp"
#include "OpenCVWindowDetail.hpp"
#include <QtWidgets/qfiledialog.h>
//#include <QtCharts>
OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i){
    auto ans=OpenCVWindow::insertImage(i);
    auto item=new OpenCVVerticalItems(ans);
    item->addWidget(new ControlItem(ans),true);
    ans->resize(i.width()+300,
                i.height()+300
                );
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

    typedef std::function<QImage(const QImage &)> FunctionType;
    auto function=std::shared_ptr<FunctionType>(
        new FunctionType([pack](const QImage & inputImage)->QImage {
        if (inputImage.isNull()) { return{}; }
        try {
           return inputImage.convertToFormat(QImage::Format_Grayscale8);
        }
        catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
            return inputImage;
        }
    }));

    rootItem_->setAlgFunction(function);
}

namespace opencv_2HSV{
extern void run(OpenCVWindow * window) try{

    /*测试图片显示*/
    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

            for (const auto & image_name:images_names) {
            window->insertImage(QImage(image_name))
                ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        }
    }
    /*测试柱状图*/
    window->insertHist({ 1,2,3,4,5 })->setWindowTitle(u8"柱状图"_qs);
    /*测试散点图*/
    auto scatter=window->insertScatter({ {0,0},{1,1},{2,2} });
    scatter->setCentrePointPaint(
        std::shared_ptr< std::function<void(QPainter *)> >(
        new std::function<void(QPainter *)>{
        [](QPainter * painter) {
        painter->setBrush(Qt::transparent);
        painter->setPen(QPen(QColor(0,0,0),1));
        painter->drawRect(QRect{-10,-10,20,20});
    }
    }
        )
        );
    scatter->setWindowTitle(u8"散点图"_qs);

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

