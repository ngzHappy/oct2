/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_matchTemplate_run_exception.cpp"
#include "OpenCVWindowDetail.hpp"
#include "ControlItem.hpp"
#include <QtWidgets/qfiledialog.h>
//#include <QtCharts>

OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage inputImage) {
    OpenCVImageItem * ans=OpenCVWindow::insertImage(inputImage);
    auto * var_vi=new OpenCVVerticalItems(ans);
    var_vi->addWidget(new ControlItem(ans));
    ans->resize(
        inputImage.width()+360,
        inputImage.height()+360
    );
    return ans;
}

void ControlItem::on_do_button_clicked() {
    try {
        cv::Mat templateImage=OpenCVUtility::tryRead(template_image_);
        int mode=getMode();
        auto * algFun=new std::function<QImage(const QImage &)>(
            [templateImage,mode](const QImage & imageInput)->QImage {
            try {
                cv::Mat image=OpenCVUtility::tryRead(imageInput);
                cv::Mat ans;
                cv::matchTemplate(image,templateImage,ans,mode);
                cv::normalize(ans,ans,0,255,cv::NORM_MINMAX);
                return OpenCVUtility::tryRead(ans);
            }
            catch (const cv::Exception &e) {
                opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
                return imageInput;
            }
        }
            );
        rootItem_->setAlgFunction(
            std::shared_ptr<std::function<QImage(const QImage &)>>(
            algFun));
    }
    catch (const cv::Exception &e) {
        opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
    }
}


void ControlItem::on_open_template_image_clicked() {
    QString imageName=QFileDialog::getOpenFileName();
    if (imageName.isEmpty()) { return; }
    template_image_=
        QImage(imageName).convertToFormat(QImage::Format_Grayscale8);
    _p_update_template_image_show_();
}

void ControlItem::on_open_image_clicked() {
    QString imageName=QFileDialog::getOpenFileName();
    if (imageName.isEmpty()) { return; }
    rootItem_->setImage(
        QImage(imageName).convertToFormat(QImage::Format_Grayscale8));
}

namespace opencv_matchTemplate {
extern void run(OpenCVWindow * window) try {

    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");
    std::intptr_t count_=0;
    for (const auto & image_name:images_names) {
        window->insertImage(
            QImage(image_name).convertToFormat(QImage::Format_Grayscale8)
        )->setWindowTitle(u8"%1"_qs.arg(++count_));
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

