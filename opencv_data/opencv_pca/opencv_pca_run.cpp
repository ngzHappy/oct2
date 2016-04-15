/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <vector>
#include "private/opencv_pca_run_exception.cpp"

namespace {

inline std::vector< cv::Point2d > genPoints() {
    enum { SIZE=100 };
    std::vector< cv::Point2d > ans;
    ans.reserve(SIZE);
    for (intptr_t i=0; i<SIZE; ++i) {
        double value_=std::sin(std::rand());
        double noise_dx_=std::cos(std::rand())/10;
        double noise_dy_=std::cos(std::rand())/10;
        ans.emplace_back(value_+noise_dx_,value_+noise_dy_);
    }
    return std::move(ans);
}

}

namespace {

void draw_axis_array_(
    QPainter * painter,
    double dx1,double dy1,
    double dx2,double dy2,
    double axix_len=100,
    double array_len=30,
    double array_weight=15
    ) {
    array_weight/=2;
    double len1=std::sqrt(dx1*dx1+dy1*dy1);
    double len2=std::sqrt(dy2*dy2+dx2*dx2);
    dx1/=len1; dy1/=len1;
    dx2/=len2; dy2/=len2;

    const double pox1_x=dx1*axix_len;
    const double pox1_y=dy1*axix_len;
    const double pox2_x=dx2*axix_len;
    const double pox2_y=dy2*axix_len;

    QPainterPath path_;
    path_.moveTo(0,0);
    path_.lineTo(pox1_x,pox1_y);
    path_.lineTo(pox1_x-dy1*array_weight,pox1_y+dx1*array_weight);
    path_.lineTo(pox1_x+dx1*array_len,pox1_y+dy1*array_len);
    path_.lineTo(pox1_x+dy1*array_weight,pox1_y-dx1*array_weight);
    path_.lineTo(pox1_y,pox1_y);

    path_.moveTo(0,0);
    path_.lineTo(pox2_x,pox2_y);
    path_.lineTo(pox2_x-dy2*array_weight,pox2_y+dx2*array_weight);
    path_.lineTo(pox2_x+dx2*array_len,pox2_y+dy2*array_len);
    path_.lineTo(pox2_x+dy2*array_weight,pox2_y-dx2*array_weight);
    path_.lineTo(pox2_x,pox2_y);

    painter->setBrush(QColor(255,255,255,222));
    painter->setPen(QPen(QColor(0,0,0,222),1.2));
    painter->drawPath(path_);

}

}

namespace opencv_pca{
extern void run(OpenCVWindow * window) try{
    /*计算主成分*/
    auto data=genPoints();
    cv::Mat dataWrap(data.size(),2,CV_64FC1,
        const_cast<cv::Point2d *>(data.data()));
    cv::Mat mean;
    cv::Mat eigenvectors;
    cv::PCACompute(dataWrap,mean,eigenvectors);

    /*绘制*/
    {
        OpenCVScatterItem * item_=
            window->insertScatter(data.cbegin(),data.cend());
        std::shared_ptr< std::function<void(QPainter *)> > c_draw_{
            new std::function<void(QPainter *)>{
            [eigenvectors](QPainter * painter) {
            draw_axis_array_(painter,
                eigenvectors.at<double>(0,0),eigenvectors.at<double>(0,1),
                eigenvectors.at<double>(1,0),eigenvectors.at<double>(1,1),
                100,
                30,15);
        }} };
        item_->setCentrePointPaint(c_draw_);
        item_->setWindowTitle(u8"绘制特征向量"_qs);
    }

    cv::Mat projectAns;
    /*绘制投影*/
    {
        cv::PCAProject(dataWrap,mean,eigenvectors,projectAns);
        auto begin_=reinterpret_cast<cv::Point2d *>(projectAns.data);
        auto end_=begin_+projectAns.rows;
        OpenCVScatterItem * item_=window->insertScatter(begin_,end_);
        item_->setWindowTitle(u8"绘制投影后的数据"_qs);
        item_->resize(512,20);
    }

    cv::Mat backProjectAns;
    /*绘制反投影数据*/
    {
        cv::PCABackProject(projectAns,mean,eigenvectors,backProjectAns);
        auto begin_=reinterpret_cast<cv::Point2d *>(backProjectAns.data);
        auto end_=begin_+backProjectAns.rows;
        OpenCVScatterItem * item_=window->insertScatter(begin_,end_);
        item_->setWindowTitle(u8"绘制反投影后的数据"_qs);
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",__LINE__,__FILE__,__func__);
}

}
