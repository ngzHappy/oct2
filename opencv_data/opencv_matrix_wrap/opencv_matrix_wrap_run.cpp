/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <OpenCVMatProxyAllocator.hpp>
#include <vector>
#include "private/opencv_matrix_wrap_run_exception.cpp"
namespace opencv_matrix_wrap{
extern void run(OpenCVWindow *) try{

    std::shared_ptr< std::vector<double> >
        data_(new std::vector<double>{ 1,2,3,4,5 });
    cv::Mat matrix_(data_->size(),1,CV_64FC1,data_->data(),0);
    matrix_.u=OpenCVUserDataAllocator::instance()->allocate(
        new auto(data_),
        [](void * d_) {
        std::cout<<"delete test data"<<std::endl;
        delete reinterpret_cast<
        std::shared_ptr< std::vector<double> > *>(d_); }
        );

    std::cout<<matrix_<<std::endl;

}
catch (const cv::Exception &e) {
    opencv_exception::error(e);
}

}
