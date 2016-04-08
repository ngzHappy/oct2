/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <opencv2/stitching.hpp>

extern void run(OpenCVWindow * window) {
    std::vector< cv::Mat > images_;
    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        for (const auto & image_name:images_names) {
            QImage image_(image_name);
            window->insertImage(image_)
                ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
            images_.push_back(OpenCVUtility::tryRead(image_));
        }
    }
    auto stitcher=cv::createStitcher(true/*try_use_gpu*/);
    cv::Mat ans;
    stitcher->stitch(images_,ans);

    auto * item=window->insertChartImage(OpenCVUtility::tryRead(std::move(ans)));
    item->setWindowTitle(u8"全景图"_qs);
    item->setGridLineVisible(false,false);
}

