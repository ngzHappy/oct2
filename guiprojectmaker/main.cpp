#include "MainWindow.hpp"
#include <QApplication>
#include <QtCore/qtextcodec.h>

int main(int argc, char *argv[])
{
    /*设置本地编码*/
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(LOCAL_CODEC_));

    QApplication app(argc, argv);

    MainWindow *window = new MainWindow;
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setWindowTitle(QObject::trUtf8(u8"项目生成器"));
    window->show();

    return app.exec();
}



