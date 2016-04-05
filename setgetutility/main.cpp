#include "MainWindow.hpp"
#include <QApplication>
#include <QtGui/qimage.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    {
        QImage * image = new QImage("null.png");
        delete image;
    }

    MainWindow window;
    window.setClassName("Class");
    window.setValueName("value");
    window.setValueType("std::string");
    window.show();

    return app.exec();
}
