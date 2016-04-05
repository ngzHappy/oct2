/*MainWiindow.hpp*/
#ifndef MAIINWINDOW_HPP
#define MAIINWINDOW_HPP

#include <QtWidgets/qmainwindow.h>
#include <core_utility.hpp>
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

