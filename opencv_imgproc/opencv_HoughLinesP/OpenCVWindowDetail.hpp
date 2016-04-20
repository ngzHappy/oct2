/*OpenCVWindowDetail.hpp*/
#ifndef OPENCVWINDOWDETAIL_HPP
#define OPENCVWINDOWDETAIL_HPP

class OpenCVImageItem;
#include <OpenCVWindow.hpp>

class OpenCVWindowDetail : public OpenCVWindow
{
    Q_OBJECT
MACRO_PROTECTED:
    typedef OpenCVWindow P;
public:
    OpenCVWindowDetail(QWidget * parent=nullptr);
    ~OpenCVWindowDetail();

    OpenCVImageItem * insertImage(QImage)override;
private:

};

#endif // OPENCVWINDOWDETAIL_HPP

