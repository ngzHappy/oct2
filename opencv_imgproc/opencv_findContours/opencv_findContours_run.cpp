/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

extern void run(OpenCVWindow * window) {

    /*测试图片显示*/
    {
        intptr_t count_=0;

        /*从配置文件读入图片路径*/
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        for (const auto & image_name:images_names) {
            QImage input_image_=QImage(image_name);

            const auto height_=input_image_.height();
            const auto width_=input_image_.width();

            window->insertImage(input_image_)
                ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

            if (height_<=0) { continue; }
            if (width_<=0) { continue; }

            input_image_=
                input_image_.convertToFormat(QImage::Format_Grayscale8);
            
            auto * item_ = window->insertChartImage(input_image_);
            cv::Mat mat=OpenCVUtility::tryRead(input_image_);
            std::vector<std::vector<cv::Point>> ans;

            /*查找轮廓*/
            cv::findContours(
                mat,ans,
                cv::RETR_EXTERNAL,
                cv::CHAIN_APPROX_SIMPLE 
                );

           if (ans.empty()) { continue; }

           item_->setWindowTitle(u8"第%1幅图片轮廓"_qs.arg(count_));
           
          
           for (auto i=ans.begin(); i!=ans.end();++i) {
               std::vector<cv::Point> & d=*i;
               item_->insertLine(d.begin(),d.end(),true)
                   ->setPen(QPen(QColor(200,200,100,150),2));
           }
        }
    }
  

}

