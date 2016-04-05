/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <vector>
#include <sstream>

namespace {

inline std::vector< cv::Point2d > genPoints() {
    enum {SIZE=100};
    std::vector< cv::Point2d > ans;
    ans.reserve(SIZE);
    for (intptr_t i=0; i<SIZE;++i) {
        double value_=std::sin(std::rand());
        double noise_dx_=std::cos(std::rand())/10;
        double noise_dy_=std::cos(std::rand())/10;
        ans.emplace_back( value_+noise_dx_,value_+noise_dy_ );
    }
    return std::move(ans);
}

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
    path_.lineTo( pox1_x,pox1_y );
    path_.lineTo( pox1_x-dy1*array_weight,pox1_y+dx1*array_weight );
    path_.lineTo( pox1_x+dx1*array_len,pox1_y+dy1*array_len );
    path_.lineTo( pox1_x+dy1*array_weight,pox1_y-dx1*array_weight );
    path_.lineTo( pox1_y,pox1_y  );

    path_.moveTo(0,0);
    path_.lineTo( pox2_x,pox2_y );
    path_.lineTo( pox2_x-dy2*array_weight,pox2_y+dx2*array_weight );
    path_.lineTo( pox2_x+dx2*array_len,pox2_y+dy2*array_len );
    path_.lineTo( pox2_x+dy2*array_weight,pox2_y-dx2*array_weight );
    path_.lineTo( pox2_x,pox2_y  );

    painter->setBrush(QColor(255,255,255,222));
    painter->setPen(QPen(QColor(0,0,0,222),1.2));
    painter->drawPath(path_);

}

}

extern void run(OpenCVWindow * window) {
    
    std::vector< cv::Point2d > testPoints = genPoints();
    OpenCVScatterItem * item_ =
        window->insertScatter(testPoints.cbegin(),testPoints.cend());
    
    /*令每个点减去均值*/
    {
        cv::Point2d mean_=
            std::accumulate(testPoints.begin(),testPoints.end(),cv::Point2d{ 0,0 });
        mean_.x/=testPoints.size();
        mean_.y/=testPoints.size();
        for (auto & point:testPoints) { point-=mean_; }
    }

    /*用opencv mat包装数据*/
    cv::Mat diff(
        testPoints.size(),2,
        CV_64FC1,
        const_cast<cv::Point2d *>(testPoints.data()));
   
    /*保存成MATLAB格式*/
    {
        std::stringstream data_diff;
        data_diff<<"data_diff"
            <<cv::format(diff,cv::Formatter::FMT_MATLAB)<<std::endl;
        QFile outPutFile ( qApp->applicationDirPath() + "/simple_pca_data.m");
        outPutFile.open(QFile::Text|QFile::WriteOnly);
        const auto data__= readAll(data_diff) ;
        outPutFile.write(data__.first,data__.second);
        outPutFile.write("\n");
        /*MATLAB 使用 princomp进行主成分分析*/
    }

    cv::Mat transpose_diff;
    cv::transpose(diff,transpose_diff);
    cv::Mat A=transpose_diff*diff;
    cv::Mat eigenvalues,eigenvectors;
    /*计算特征值特征向量*/
    cv::eigen(A,eigenvalues,eigenvectors);
    std::cout<<"eigen values:"<<std::endl
        <<eigenvalues<<std::endl;
    /*注意:opencv特征向量按行存储*/
    std::cout<<"eigen vectors"<<std::endl
        <<eigenvectors<<std::endl;

    std::shared_ptr< std::function<void(QPainter *)> > c_draw_{
        new std::function<void(QPainter *)>{
        [eigenvectors](QPainter * painter) {
        draw_axis_array_(painter,
            eigenvectors.at<double>(0,0),eigenvectors.at<double>(0,1),
            eigenvectors.at<double>(1,0),eigenvectors.at<double>(1,1),
            100,
            30,15);
    }}};
    item_->setCentrePointPaint(c_draw_);
    item_->setWindowTitle(u8"绘制特征向量"_qs);
}

