const char *_MainWindow_hpp_cpp = u8R"=_____=(/*MainWiindow.hpp*/
#ifndef MAIINWINDOW_HPP
#define MAIINWINDOW_HPP

#include <QtWidgets/qmainwindow.h>
#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif
class OpenCVWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT
MACRO_PROTECTED:
    typedef QMainWindow P;
    OpenCVWindow * openCVWindow_;
public:
    explicit MainWindow(QWidget *parent=0);
    ~MainWindow();

    OpenCVWindow * getOpenCVWindow()const { return openCVWindow_; }

signals:

public slots:
};

#endif // MAIINWINDOW_HPP

)=_____=";

