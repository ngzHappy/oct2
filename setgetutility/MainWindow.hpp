#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include <memory>
#include <QMainWindow>

class _MainWindowPrivate;
class MainWindow : public QMainWindow
{
    Q_OBJECT
MACRO_PROTECTED:
    _MainWindowPrivate * thisp_=nullptr;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    const QString & getClassName()const;
    const QString & getValueName()const;
    const QString & getValueType()const;
    void setClassName(const QString & v);
    void setValueName(const QString & v);
    void setClassName(QString && v);
    void setValueName(QString && v);
    void setValueType(QString &&);
    void setValueType(const QString &);
public slots:
    void updateValue();
};

#endif // MAINWINDOW_HPP
