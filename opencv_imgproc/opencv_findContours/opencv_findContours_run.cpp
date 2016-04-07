/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

namespace {
void draw(
    OpenCVWindow * window,
    std::vector<std::vector<cv::Point>> &ans,
    const int &width_,
    const int &height_,
    const intptr_t &count_) {
    /*将轮廓按照从大到小排列*/
    std::sort(ans.begin(),ans.end(),
        [](const std::vector<cv::Point> & l,
        const std::vector<cv::Point> & r) {
        return r.size()<l.size();
    });
    if (ans[0].empty()) { return; }

    /*插入第一个轮廓*/
    QList<QPointF> data_;
    data_.reserve(ans[0].size());
    for (const auto & i:ans[0]) {
        data_.push_back(QPointF(i.x,height_-i.y));
    }

    auto * item_=window->insertLineSeries(data_);
    item_->getLineSeries()->append(ans[0].begin()->x,
        height_-(ans[0].begin()->y));

    /*设置坐标系大小与图片一致*/
    item_->getChart()->axisX()->setRange(0,width_);
    item_->getChart()->axisY()->setRange(0,height_);

    item_->resize(width_*1.3,height_*1.3);

    /*插入剩余轮廓*/
    auto pos_=ans.begin();
    for (++pos_; pos_!=ans.end(); ++pos_) {
        if (pos_->empty()) { continue; }
        data_.clear();
        for (const auto & i:*(pos_)) {
            data_.push_back(QPointF(i.x,height_-i.y));
        }
        data_.push_back(
            QPointF(pos_->begin()->x,
            height_-pos_->begin()->y)
            );
        QtCharts::QLineSeries * series=new QtCharts::QLineSeries;
        series->append(data_);
        item_->getChart()->addSeries(series);
        item_->getChart()->setAxisX(
            item_->getChart()->axisX(item_->getLineSeries()),
            series
            );
        item_->getChart()->setAxisY(
            item_->getChart()->axisY(item_->getLineSeries()),
            series
            );
        series->setPen(item_->getLineSeries()->pen());
        series->setBrush(item_->getLineSeries()->brush());
    }

    /*设置轮廓标题*/
    item_->setWindowTitle(u8"第%1幅图片轮廓"_qs.arg(count_));
}

}


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
            
            cv::Mat mat=OpenCVUtility::tryRead(input_image_);
            std::vector<std::vector<cv::Point>> ans;

            /*查找轮廓*/
            cv::findContours(
                mat,ans,
                cv::RETR_EXTERNAL,
                cv::CHAIN_APPROX_SIMPLE 
                );

           if (ans.empty()) { continue; }

           draw(window,ans,width_,height_,count_);
        }
    }
  

}

