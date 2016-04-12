#include "MainWindow.hpp"
#include <QtQuick/QtQuick>

MainWindow::MainWindow(){
    this->rootContext()
            ->setContextProperty("rootWindow",this);
}

MainWindow::~MainWindow(){

}
