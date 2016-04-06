const char *_MainWindow_cpp = u8R"=_____=(/*MainWindow.cpp*/
#include "MainWindow.hpp"
#include "OpenCVWindowDetail.hpp"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qmenubar.h>

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
    QAction * openImage_=menuBar()->addAction(trUtf8(u8"打开图片"));
    connect(openImage_,&QAction::triggered,this,[this](bool) {openImage(); });
}

void MainWindow::openImage() {
    const QString files_=QFileDialog::getOpenFileName(
        nullptr,
        u8R"(选择图片)"_qs,
        ""/*dir*/,
        ""/*filter*/
        );

    if (files_.isEmpty()) { return; }
    getOpenCVWindow()->insertImage( QImage(files_) );
    
}

/*析构主窗口*/
MainWindow::~MainWindow() {

}

)=_____=";
