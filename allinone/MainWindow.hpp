#if !defined(MAIN__WINDOW__HPP__)
#define MAIN__WINDOW__HPP__

#include <QQuickView>

class MainWindow:public QQuickView{
    Q_OBJECT
private:
    typedef QQuickView P;
public:
    MainWindow();
    virtual ~MainWindow();
};

#endif

