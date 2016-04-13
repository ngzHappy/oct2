#ifndef MWANWINDOW_HPP
#define MWANWINDOW_HPP

#include <QtGui/qimage.h>
#include <QtWidgets/qmainwindow.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    QImage image_;
    QString to_dir_;
private:
    typedef QMainWindow P;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void save();
    void select();

public:
    void setDstDir(const QString& /*dstDir*/);
    void setDstDir(QString&& /*dstDir*/);
    const QString & getDstDir() const;
    const QString & dstDir() const{ return getDstDir();}
    void setImage(const QImage& /*image*/);
    void setImage(QImage&& /*image*/);
    const QImage & getImage() const;
    const QImage & image() const{ return getImage();}
private:
    template<typename _t_IMAGE_t__>
    void _p_setImage(_t_IMAGE_t__ && /*image*/);
    template<typename _t_DSTDIR_t__>
    void _p_setDstDir(_t_DSTDIR_t__ && /*dstDir*/);
};

#endif // MWANWINDOW_HPP
