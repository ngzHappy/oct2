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

QString MainWindow::getProjectName(int argN){
    QQuickItem * varItem = this->rootObject();
    QVariant varAns;
    QMetaObject::invokeMethod(varItem,
                              "getProjectName",
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, varAns),
                              Q_ARG(QVariant, argN));
    return varAns.toString();
}
QString MainWindow::getStartString(int argN){
    QQuickItem * varItem = this->rootObject();
    QVariant varAns;
    QMetaObject::invokeMethod(varItem,
                              "getStartString",
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, varAns),
                              Q_ARG(QVariant, argN));
    return varAns.toString();
}

void MainWindow::startApplication(QString argAppName,QString argStartString){
    qDebug()<<argAppName
           <<argStartString
          <<getProjectName(0)
           <<getStartString(0);

}
