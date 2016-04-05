#define MACRO_PROTECTED public

#include "MainWindow.hpp"
#include "SetGetUtility.hpp"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qtextbrowser.h>
#include <QtWidgets/qtextedit.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtCore/qdebug.h>

class _MainWindowPrivate{
public:
    QFormLayout * formlayout_;
    QLineEdit * className_;
    QLineEdit * valueName_;
    QLineEdit * valueType_;
    QTextBrowser * textBrowser_;
    SetGetUtility * setGetUtility_;
    _MainWindowPrivate(MainWindow * super,QVBoxLayout * layout_){
        setGetUtility_ = new SetGetUtility;
        valueType_ = new QLineEdit;
        formlayout_ = new QFormLayout;
        className_=new QLineEdit;
        valueName_=new QLineEdit;
        textBrowser_=new QTextBrowser;
        layout_->addLayout(formlayout_);
        formlayout_->addRow(QString::fromUtf8(u8R"(类名)"),className_);
        formlayout_->addRow(QString::fromUtf8(u8R"(变量类型)"),valueType_);
        formlayout_->addRow(QString::fromUtf8(u8R"(变量名)"),valueName_);
        layout_->addWidget( textBrowser_ );

        super->connect(
                    className_,&QLineEdit::editingFinished,
                    super,[super,this](){ super->setClassName( className_->text() ); }
        );

        super->connect(
                    valueType_,&QLineEdit::editingFinished,
                    super,[super,this](){ super->setValueType(valueType_->text() ); }
        );

        super->connect(
                    valueName_,&QLineEdit::editingFinished,
                    super,[super,this](){ super->setValueName( valueName_->text() ); }
        );

    }
    ~_MainWindowPrivate(){
        delete setGetUtility_;
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    setCentralWidget(new QWidget);
    QWidget * centralWidget_ = centralWidget();
    QVBoxLayout * layout_ = new QVBoxLayout;
    centralWidget_->setLayout(layout_);
    layout_->setSpacing(0);
    layout_->setMargin(0);
    thisp_ = new _MainWindowPrivate(this,layout_);
    this->resize(512,512);
    this->setMinimumHeight(512);
    this->setMinimumWidth(256);
}

MainWindow::~MainWindow(){
    delete thisp_;
}

const QString & MainWindow::getClassName()const{
    return thisp_->setGetUtility_->getClassName();
}

const QString & MainWindow::getValueName()const{
    return thisp_->setGetUtility_->getValueName();
}

void MainWindow::setClassName(const QString & v){
    if( v == getClassName() ){return;}
    thisp_->setGetUtility_->setClassName(v);
    updateValue();
}

void MainWindow::setValueName(const QString & v){
    if( v==getValueName() ){return;}
    thisp_->setGetUtility_->setValueName(v);
    updateValue();
}

void MainWindow::setClassName(QString && v){
    if( v == getClassName() ){return;}
    thisp_->setGetUtility_->setClassName(std::move(v));
    updateValue();
}

const QString &  MainWindow::getValueType()const{
    return thisp_->setGetUtility_->getValueType();
}

void MainWindow::setValueType(QString && v){
    if( v==getValueType() ){return;}
    thisp_->setGetUtility_->setValueType(std::move(v));
    updateValue();
}
void MainWindow::setValueType(const QString & v){
    if( v==getValueType() ){return;}
    thisp_->setGetUtility_->setValueType(v);
    updateValue();
}

void MainWindow::setValueName(QString && v){
    if( v==getValueName() ){return;}
    thisp_->setGetUtility_->setValueName(std::move(v));
    updateValue();
}

void MainWindow::updateValue(){

    thisp_->valueName_->blockSignals(true);
    thisp_->valueType_->blockSignals(true);
    thisp_->className_->blockSignals(true);

    thisp_->valueName_->setText( getValueName() );
    thisp_->valueType_->setText( getValueType() );
    thisp_->className_->setText( getClassName() );

    thisp_->valueName_->blockSignals(false);
    thisp_->valueType_->blockSignals(false);
    thisp_->className_->blockSignals(false);

    QString value_ans_ = (*(thisp_->setGetUtility_))();
    thisp_->textBrowser_->setPlainText( std::move(value_ans_) );

    /*qDebug().noquote()<<value_ans_;*/
}


