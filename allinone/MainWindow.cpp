#include "MainWindow.hpp"
#include <QtCore/qdebug.h>
#include <QtQuick/QtQuick>
#include <QtCore/qprocess.h>

MainWindow::MainWindow(){
    this->rootContext()
            ->setContextProperty("rootWindow",this);
    this->setMinimumHeight(300);
    this->setMinimumWidth(600);
}

MainWindow::~MainWindow(){
    _save();
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
    auto varAppName=qApp->applicationDirPath()+"/"+argAppName.trimmed();
    varAppName+=" "+argStartString.trimmed();
    if(false == QProcess::startDetached(varAppName.trimmed())){
#if defined(Q_OS_WIN)
        varAppName=qApp->applicationDirPath()+"/"+argAppName.trimmed()+".exe";
        varAppName+=" "+argStartString.trimmed();
        if (false==QProcess::startDetached(varAppName.trimmed()))
#endif
        {
            qDebug()<<"can not start:"<<argAppName;
        }
    }

}
