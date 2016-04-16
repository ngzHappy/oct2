/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_morphologyEx_run_exception.cpp"
//#include <QtCharts>

namespace opencv_morphologyEx {
extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    for (const auto & image_name:images_names) {

        QImage input_image=QImage(image_name);
        input_image=input_image.convertToFormat(QImage::Format_Grayscale8);

        window->insertImage(input_image)
            ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));

        cv::Mat mat=OpenCVUtility::tryRead(input_image);

        try{
            cv::Mat ans;
            cv::morphologyEx(mat,ans,cv::MORPH_OPEN,
                cv::getStructuringElement(cv::MORPH_RECT,{ 5,5 }));
            window->insertImage(ans)
                ->setWindowTitle(u8"第%1幅图片MORPH_OPEN"_qs.arg(count_));
        }
        catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
        }

        try{
            cv::Mat ans;
            cv::morphologyEx(mat,ans,cv::MORPH_CLOSE,
                cv::getStructuringElement(cv::MORPH_RECT,{ 5,5 }));
            window->insertImage(ans)
                ->setWindowTitle(u8"第%1幅图片MORPH_CLOSE"_qs.arg(count_));
        }
        catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
        }

        try{
            cv::Mat ans;
            cv::morphologyEx(mat,ans,cv::MORPH_GRADIENT,
                cv::getStructuringElement(cv::MORPH_RECT,{ 5,5 }));
            window->insertImage(ans)
                ->setWindowTitle(u8"第%1幅图片MORPH_GRADIENT"_qs.arg(count_));
        }catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
        }

        try{
            cv::Mat ans;
            cv::morphologyEx(mat,ans,cv::MORPH_TOPHAT,
                cv::getStructuringElement(cv::MORPH_RECT,{ 5,5 }));
            window->insertImage(ans)
                ->setWindowTitle(u8"第%1幅图片MORPH_TOPHAT "_qs.arg(count_));
        }catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
        }

        try{
            cv::Mat ans;
            cv::morphologyEx(mat,ans,cv::MORPH_BLACKHAT,
                cv::getStructuringElement(cv::MORPH_RECT,{ 5,5 }));
            window->insertImage(ans)
                ->setWindowTitle(u8"第%1幅图片MORPH_BLACKHAT"_qs.arg(count_));
        }catch (const cv::Exception &e) {
            opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
        }

    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

