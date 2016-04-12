#include "MainWindow.hpp"
#include <QtCore/qdebug.h>
#include <QtQuick/QtQuick>

MainWindow::MainWindow(){
    this->rootContext()
            ->setContextProperty("rootWindow",this);
    this->setMinimumHeight(300);
    this->setMinimumWidth(600);
}

MainWindow::~MainWindow(){

}

void MainWindow::startDataView(QString s){
    qDebug()<<s;

}
