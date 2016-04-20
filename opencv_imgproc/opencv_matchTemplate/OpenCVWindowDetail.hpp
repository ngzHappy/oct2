/*OpenCVWindowDetail.hpp*/
#ifndef OPENCVWINDOWDETAIL_HPP
#define OPENCVWINDOWDETAIL_HPP

#include <OpenCVWindow.hpp>

class OpenCVWindowDetail : public OpenCVWindow
{
    Q_OBJECT
MACRO_PROTECTED:
    typedef OpenCVWindow P;
public:
    OpenCVWindowDetail(QWidget * parent=nullptr);
    ~OpenCVWindowDetail();

public:
    OpenCVImageItem * insertImage(QImage )override;
};

#endif // OPENCVWINDOWDETAIL_HPP

