/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_bilateralFilter_run_exception.cpp"
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qcombobox.h>
//#include <QtCharts>

namespace opencv_bilateralFilter {


namespace {
cv::BorderTypes TitleBar2CVBorderType[]{
    cv::BORDER_REFLECT_101,
    cv::BORDER_CONSTANT,
    cv::BORDER_REPLICATE,
    cv::BORDER_REFLECT,
    cv::BORDER_WRAP,
};

class TitleBar :public QWidget {
    OpenCVImageItem * const item_;
    QSpinBox * d_;
    QDoubleSpinBox * sigmaColor_;
    QDoubleSpinBox * sigmaSpace_;
    QPushButton * doButton_;
    QComboBox * borderType_;
    //BORDER_CONSTANT 	
    //BORDER_REPLICATE 	
    //BORDER_REFLECT 	
    //BORDER_WRAP 	
    //BORDER_REFLECT_101 	
public:
    TitleBar(OpenCVImageItem * _i):item_(_i) {
        /*初始化控件*/
        auto * layout_=new QVBoxLayout;
        this->setLayout(layout_);
        auto * formLayout_=new QFormLayout;
        layout_->addLayout(formLayout_);
        d_=new QSpinBox;
        formLayout_->addRow("d",d_);
        sigmaColor_=new QDoubleSpinBox;
        formLayout_->addRow("sigmaColor",sigmaColor_);
        sigmaSpace_=new QDoubleSpinBox;
        formLayout_->addRow("sigmaSpace",sigmaSpace_);
        borderType_=new QComboBox;
        formLayout_->addRow("borderType",borderType_);
        doButton_=new QPushButton;
        layout_->addWidget(doButton_);
        layout_->setSpacing(0);
        layout_->setMargin(0);
        formLayout_->setMargin(0);
        formLayout_->setSpacing(0);
        sigmaSpace_->setMinimum(-999);
        sigmaSpace_->setMaximum(999);
        sigmaSpace_->setSingleStep(0.1);
        sigmaColor_->setMinimum(-999);
        sigmaColor_->setMaximum(999);
        sigmaColor_->setSingleStep(0.1);
        d_->setMaximum(999);
        d_->setMinimum(-999);
        d_->setSingleStep(1);
        doButton_->setText(u8"确定"_qs);

        /*设置信号槽*/
        connect(doButton_,&QPushButton::clicked,this,[this](bool) {do_eval(); });
        connect(sigmaColor_,&QDoubleSpinBox::editingFinished,
            this,[this]() {do_eval(); });
        connect(sigmaSpace_,&QDoubleSpinBox::editingFinished,
            this,[this]() {do_eval(); });
        connect(d_,&QSpinBox::editingFinished,
            this,[this]() {do_eval(); });

        const static QStringList items__{
            "BORDER_REFLECT_101"/*0*/,
            "BORDER_CONSTANT"/*1*/,
            "BORDER_REPLICATE"/*2*/,
            "BORDER_REFLECT"/*3*/,
            "BORDER_WRAP"/*4*/,
        };

        /*设置数据*/
        borderType_->addItems(items__);
        d_->setValue(25);
        sigmaColor_->setValue(50);
        sigmaSpace_->setValue(12.5);

    }
    ~TitleBar() { }

    void do_eval() try {

        const int d=d_->value();
        const double s_c=sigmaColor_->value();
        const double s_s=sigmaSpace_->value();
        const cv::BorderTypes type=
            TitleBar2CVBorderType[std::min(4,borderType_->currentIndex())];

        std::shared_ptr<std::function<QImage(const QImage &)>> run_function
            =std::make_shared<std::function<QImage(const QImage &)>>(
                std::function<QImage(const QImage &)> {
            [=](const QImage & image_) ->QImage {
                try {
                    cv::Mat mat=OpenCVUtility::tryRead(image_);
                    mat.convertTo(mat,CV_32FC3);
                    cv::Mat ans;
                    cv::bilateralFilter(mat,ans,d,s_c,s_s,type);
                    return OpenCVUtility::tryRead(ans);
                }
                catch (const cv::Exception &e) {
                    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
                    return image_;
                }
            }
        }
        );

        item_->setAlgFunction(std::move(run_function));

    }
    catch (const cv::Exception &e) {
        opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
    }


};
}

extern void run(OpenCVWindow * window) try {

    intptr_t count_=0;
    const auto images_names=
        CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

    if (images_names.isEmpty()) { return; }

    for (const auto & image_name:images_names) {

        auto image=QImage(image_name).convertToFormat(QImage::Format_RGB888);

        auto * item=window->insertImage(image);
        item->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        window->insertImage(image)
            ->setWindowTitle(u8"第%1幅原始图片"_qs.arg(count_));

        OpenCVVerticalItems * control_=new OpenCVVerticalItems(item);
        control_->addWidget(new TitleBar(item));
    }



}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

