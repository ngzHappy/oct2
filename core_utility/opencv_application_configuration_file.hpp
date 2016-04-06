#if !defined(_OPENCV_APPLICATION_CONFIGURATION_FILE )
#define _OPENCV_APPLICATION_CONFIGURATION_FILE

#include "core_utility.hpp"

class CORE_UTILITYSHARED_EXPORT OpenCVApplicationConfigurationFile {
MACRO_PROTECTED:
    static std::shared_ptr<lua_State> L_;
    lua_State * L__=nullptr;
    OpenCVApplicationConfigurationFile(lua_State *_L):L__(_L){}
public:
    OpenCVApplicationConfigurationFile(
        QByteArray /*argv*/,
        const char * /*buildpath*/,
        const char * /*lua file name like abc.lua*/);
    ~OpenCVApplicationConfigurationFile();
    QStringList getInputImagesNames(const QStringList &/*default*/)const;
    QStringList getInputImagesNames()const { return getInputImagesNames(QStringList{}); }
    QStringList getInputImagesNames(const QString & _default_)const {return getInputImagesNames(QStringList{_default_});}
MACRO_PROTECTED:
    QByteArray getLocalTextCodecName(const QByteArray &/*default*/)const;
};

#endif



