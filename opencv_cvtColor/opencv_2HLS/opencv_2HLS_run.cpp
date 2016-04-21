/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_2HLS_run_exception.cpp"
#include "ControlItem.hpp"
#include "OpenCVWindowDetail.hpp"
#include <QtWidgets/qfiledialog.h>
//#include <QtCharts>
OpenCVImageItem * OpenCVWindowDetail::insertImage(QImage i){
    auto ans=OpenCVWindow::insertImage(i.convertToFormat(QImage::Format_RGBA8888));
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

    typedef std::function<QImage(const QImage &)> FunctionType;
    auto function=std::shared_ptr<FunctionType>(
        new FunctionType([pack](const QImage & inputImage)->QImage {
        if (inputImage.isNull()) { return{}; }
        try {
            cv::Mat image=OpenCVUtility::tryRead(
                inputImage.convertToFormat(QImage::Format_RGBA8888));
            image.convertTo(image,CV_32FC4);

            /*获得rgba,用于保存alpha*/
            std::vector<cv::Mat> rgba{4};
            cv::split(image,rgba);
            {
                std::vector<cv::Mat> rgb{rgba[0],rgba[1],rgba[2]};
                cv::merge(rgb,image);
                rgba[0].release();
                rgba[1].release();
                rgba[2].release();
            }

            /*转换到hls空间*/
            cv::cvtColor(image,image,cv::COLOR_RGB2HLS);
            
            std::vector<cv::Mat> hls;
            hls.reserve(4);
            cv::split(image,hls);
            image.release();

            /*对hls空间进行线性变换*/
            hls[0]*=pack->h; 
            hls[1]*=pack->l;
            hls[2]*=pack->s;

            if(pack->hBase!=0)hls[0]+=pack->hBase; 
            if(pack->lBase!=0)hls[1]+=pack->lBase;
            if(pack->sBase!=0)hls[2]+=pack->sBase;

            /*将hls重新转换为rgb*/
            cv::merge(hls,image);
            cv::cvtColor(image,image,cv::COLOR_HLS2RGB);
            
            /*将rgb+a组成rgba*/
            cv::split(image,hls);
            hls.push_back(rgba[3]);
            cv::merge(hls,image);

            /*清空无用数据*/
            hls.clear();
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

namespace opencv_2HLS{
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

