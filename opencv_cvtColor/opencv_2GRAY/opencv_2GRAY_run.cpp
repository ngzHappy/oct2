/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_2GRAY_run_exception.cpp"
#include "ControlItem.hpp"
#include "OpenCVWindowDetail.hpp"
#include <QtWidgets/qfiledialog.h>
//#include <QtCharts>

OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i) {
    auto ans=OpenCVWindow::insertImage(i.convertToFormat(QImage::Format_RGB888));
    auto item=new OpenCVVerticalItems(ans);
    item->addWidget(new ControlItem(ans),true);
    ans->resize(768,600);
    return ans;
}

void ControlItem::on_select_image_button_clicked() {
    QString fileName=QFileDialog::getOpenFileName();
    if (fileName.isEmpty()) { return; }
    QImage image_(fileName);
    rootItem_->setImage(std::move(image_));
}

void ControlItem::on_do_button_clicked() {
    std::shared_ptr<ControlItem::Pack> pack=
        std::make_shared<ControlItem::Pack>();
    _p_init_pack(pack.get());

    typedef std::function<QImage(const QImage &)> FunctionType;
    auto function=std::shared_ptr<FunctionType>(
        new FunctionType([pack](const QImage & inputImage)->QImage {
        if (inputImage.isNull()) { return{}; }
        try {
            cv::Mat image=OpenCVUtility::tryRead(
                inputImage.convertToFormat(QImage::Format_RGB888));
            image.convertTo(image,CV_32FC3);
            {
                std::vector<cv::Mat> rgb{ 3 };
                cv::split(image,rgb);
                rgb[0]*=pack->r;
                rgb[1]*=pack->g;
                rgb[2]*=pack->b;
                if(pack->rBase!=0)rgb[0]+=pack->rBase; 
                if(pack->gBase!=0)rgb[1]+=pack->gBase; 
                if(pack->bBase!=0)rgb[2]+=pack->bBase; 
                image=rgb[0]+rgb[1]+rgb[2];
            }
            return OpenCVUtility::tryRead(image);
        }
        catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
            return inputImage;
        }
    }));

    rootItem_->setAlgFunction(function);
}

namespace opencv_2GRAY {
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

