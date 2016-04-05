/*OpenCVWindowDetail.hpp*/
#ifndef OPENCVWINDOWDETAIL_HPP
#define OPENCVWINDOWDETAIL_HPP

#include <OpenCVUtility.hpp>

class OpenCVWindowDetail : public OpenCVWindow
{
    Q_OBJECT
MACRO_PROTECTED:
    typedef OpenCVWindow P;
public:
    OpenCVWindowDetail(QWidget * parent=nullptr);
    ~OpenCVWindowDetail();

};

#endif // OPENCVWINDOWDETAIL_HPP

