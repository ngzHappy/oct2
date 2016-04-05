const char *_MainWindow_cpp = u8R"=_____=(/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "OpenCVWindowDetail.hpp"
#include <QtWidgets/qboxlayout.h>

/*中央窗口*/
namespace {
namespace __private {
class CentralWidget :public QWidget {
    QVBoxLayout * layout_;
public:
    CentralWidget(OpenCVWindow * window) {
        layout_=new QVBoxLayout;
        this->setLayout(layout_);
        layout_->setSpacing(0);
        layout_->setMargin(0);
        layout_->addWidget(window);
    }
    ~CentralWidget() {}
};
}
}

/*初始化主窗口*/
MainWindow::MainWindow(QWidget *parent):
    P(parent) {
    openCVWindow_=new OpenCVWindowDetail;
    this->setCentralWidget(new __private::CentralWidget(openCVWindow_));
    this->setMinimumSize(512,512);
    this->resize(600,600);
}

/*析构主窗口*/
MainWindow::~MainWindow() {

}

)=_____=";
