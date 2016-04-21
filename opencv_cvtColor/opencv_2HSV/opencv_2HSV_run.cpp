/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_2HSV_run_exception.cpp"
#include "ControlItem.hpp"
#include "OpenCVWindowDetail.hpp"
#include <QtWidgets/qfiledialog.h>
//#include <QtCharts>
OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i) {
    auto ans=OpenCVWindow::insertImage(i.convertToFormat(QImage::Format_RGBA8888));
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
                inputImage.convertToFormat(QImage::Format_RGBA8888));

            image.convertTo(image,CV_32FC4);

            std::vector<cv::Mat> rgba;
            std::vector<cv::Mat> hsv;

            {
                cv::split(image,rgba);
                hsv=rgba; hsv.resize(3);
                cv::merge(hsv,image);
                rgba[0].release();
                rgba[1].release();
                rgba[2].release();
                hsv.clear();
            }

            cv::cvtColor(image,image,cv::COLOR_RGB2HSV);

            cv::split(image,hsv);

            if (pack->h!=1) { hsv[0]*=pack->h; }
            if (pack->s!=1) { hsv[1]*=pack->s; }
            if (pack->v!=1) { hsv[2]*=pack->v; }

            if (pack->hBase!=0) { hsv[0]+=pack->hBase; }
            if (pack->sBase!=0) { hsv[1]+=pack->sBase; }
            if (pack->vBase!=0) { hsv[2]+=pack->vBase; }

            cv::merge(hsv,image);
            cv::cvtColor(image,image,cv::COLOR_HSV2RGB);

            cv::split(image,hsv);
            hsv.push_back(rgba[3]);
            cv::merge(hsv,image);

            hsv.clear();
            rgba.clear();

            return OpenCVUtility::tryRead(image);
        }
        catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
            return inputImage;
        }
    }));

    rootItem_->setAlgFunction(function);
}

namespace opencv_2HSV {
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

