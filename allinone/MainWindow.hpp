#if !defined(MAIN__WINDOW__HPP__)
#define MAIN__WINDOW__HPP__

#include <QtQuick/qquickview.h>

class MainWindow:public QQuickView{
    Q_OBJECT
private:
    typedef QQuickView P;
public:
    MainWindow();
    virtual ~MainWindow();
public slots:
    void startDataView(QString);
};

#endif

