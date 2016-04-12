/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <vector>
#include "private/opencv_fft_run_exception.cpp"

namespace opencv_fft{
extern void run(OpenCVWindow * window) try{

    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");
    assert(images_names.size());

    QImage image_input(images_names.first());
    image_input=image_input.convertToFormat(QImage::Format_Grayscale8);

    window->insertImage(image_input)->setWindowTitle(u8"原始图像"_qs);

    cv::Mat mat_input=OpenCVUtility::tryRead(image_input);
    assert( mat_input.channels() == 1 )/*这应当是一个灰度图像*/;

    /*计算获得dft变换所需要的长宽*/
    auto height_ = cv::getOptimalDFTSize(mat_input.rows);
    auto width_ = cv::getOptimalDFTSize(mat_input.cols);

    cv::Mat dft_real;
    /*扩展边界*/
    cv::copyMakeBorder(mat_input,dft_real,
        0/*top*/,height_-mat_input.rows/*bottom*/,
        0/*left*/,width_-mat_input.cols/*right*/,
        cv::BORDER_CONSTANT,cv::Scalar::all(0)
        );

    dft_real.convertTo(dft_real,CV_64FC1);
    cv::Mat dft_imag=cv::Mat::zeros(dft_real.size(),CV_64FC1);

    {
        cv::Mat dft_output;
        cv::merge(
            std::vector<cv::Mat>{ dft_real,dft_imag},
            dft_output);

        /*进行dft变换*/
        cv::dft(dft_output,dft_output);
        cv::split(dft_output,std::vector<cv::Mat>{ dft_real,dft_imag});
    }

    cv::Mat magI ;
    cv::magnitude(dft_real,dft_imag,magI);

    magI+=1;
    cv::log(magI,magI);//取对数
    magI= magI(cv::Rect(0,0,width_,height_));
    cv::normalize(magI,magI,0,255,CV_MINMAX);
    window->insertImage( OpenCVUtility::tryRead(magI ) )
        ->setWindowTitle(u8"变换后图像"_qs);

    {
        const auto w_2=width_/2;
        const auto h_2=height_/2;
        cv::Mat q0(magI,cv::Rect(0,0,w_2,h_2));
        cv::Mat q1(magI,cv::Rect(w_2,0,w_2,h_2));
        cv::Mat q2(magI,cv::Rect(0,h_2,w_2,h_2));
        cv::Mat q3(magI,cv::Rect(w_2,h_2,w_2,h_2));
        cv::flip(q0,q0,-1);
        cv::flip(q1,q1,-1);
        cv::flip(q2,q2,-1);
        cv::flip(q3,q3,-1);
    }
    window->insertImage( OpenCVUtility::tryRead(magI ) )
        ->setWindowTitle(u8"中心化后图像"_qs);

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

}
