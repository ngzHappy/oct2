#ifndef CREATEMAINWINDOWQML_HPP
#define CREATEMAINWINDOWQML_HPP

#include <QString>
#include <memory>
#include <map>

class CreateMainWindowQml
{
    std::map<QString,QString>data_;
public:
    CreateMainWindowQml();
    static std::shared_ptr<CreateMainWindowQml> instance();
    void createAllInOneItemQml();
    void createAllInOneMainWindowQml();
protected:
    virtual ~CreateMainWindowQml();
};

#endif // CREATEMAINWINDOWQML_HPP
