#ifndef MWANWINDOW_HPP
#define MWANWINDOW_HPP

#include <QtQuick/qquickwindow.h>
#include <QtQuick/qquickview.h>

class MainWindow : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(QString dstDir READ dstDir WRITE setDstDir NOTIFY dstDirChanged)
    Q_PROPERTY(QString imageQmlPath READ imageQmlPath WRITE setImageQmlPath NOTIFY imageQmlPathChanged)
protected:
    QString image_dir_name_;
    QImage image_;
    QString to_dir_;
private:
    typedef QQuickView P;
public:
    MainWindow(QWindow *parent  = 0);
    ~MainWindow();

public slots:
    void save();
    void selectDir();
    void selectImage();
public:
    void setImageQmlPath(const QString& /*imageQmlPath*/);
    void setImageQmlPath(QString&& /*imageQmlPath*/);
    const QString & getImageQmlPath() const;
    const QString & imageQmlPath() const{ return getImageQmlPath();}
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
    template<typename _t_IMAGEQMLPATH_t__>
    void _p_setImageQmlPath(_t_IMAGEQMLPATH_t__ && /*imageQmlPath*/);
signals:
    void dstDirChanged();
    void imageQmlPathChanged();
};

#endif // MWANWINDOW_HPP
