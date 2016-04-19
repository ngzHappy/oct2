#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP() 1

#include <QtWidgets/QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_select_pro_fullpath_clicked();
    void on_select_dir_name_clicked();
    void on_pro_fullpath_editingFinished();
    void on_dir_name_editingFinished();
    void on_project_name_editingFinished();
    void on_do_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
