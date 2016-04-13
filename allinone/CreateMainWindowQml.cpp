#include "CreateMainWindowQml.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qresource.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qfile.h>
#include <OpenCVUtility.hpp>

CreateMainWindowQml::CreateMainWindowQml()
{

}

 std::shared_ptr<CreateMainWindowQml> CreateMainWindowQml::instance(){
     std::shared_ptr<CreateMainWindowQml> varAns{
         new CreateMainWindowQml,
         [](auto * varD){delete varD;}
     };
     return std::move(varAns);
 }

 void  CreateMainWindowQml::createAllInOneItemQml(){
     QString varFileName=QDir::cleanPath(qApp->applicationDirPath()+"/AllInOneItem.qml");
     {
         QFileInfo info(varFileName);
         if(info.exists()){return;}
     }
    QFile varFile(varFileName);
    varFile.open(QIODevice::WriteOnly);
    QResource varSource(":/MainWindowAllInOne/qml/AllInOneItem.qml");
    if (varSource.isCompressed()) {
        varFile.write(qUncompress(varSource.data(),varSource.size()));
    }
    else {
        varFile.write(
            (char *)(varSource.data()),
            varSource.size()
            );
    }
    varFile.flush();
 }

 void  CreateMainWindowQml::createAllInOneMainWindowQml(){
    QString varFileName=QDir::cleanPath(qApp->applicationDirPath()+"/AllInOneMainWindow.qml");
    QFile varFile(varFileName);
    varFile.open(QIODevice::WriteOnly);
    QResource varSource(":/MainWindowAllInOne/qml/AllInOneMainWindow.qml");
    if (varSource.isCompressed()) {
        varFile.write(qUncompress(varSource.data(),varSource.size()));
    }
    else {
        varFile.write(
            (char *)(varSource.data()),
            varSource.size()
            );
    }
    varFile.flush();
 }

 CreateMainWindowQml::~CreateMainWindowQml()
 {

 }

 namespace {
 namespace __private {

 std::map<QString,QString> gen_lua_configure() {
     /*all_in_one.lua;*/
     /*all_in_one.zip;*/
     QString dirPath_ = QDir::cleanPath( qApp->applicationDirPath());
     auto _LuaState_= LuaUtility::createLuaState();
     auto * L=_LuaState_.get();

     bool isExist=false;
     {
         QFileInfo info(dirPath_+"/all_in_one.lua");
         if (info.exists()) { isExist=true; }
         LuaUtility::loadFile(L,dirPath_+"/all_in_one.lua","all_in_one.lua");
     }
     if(isExist==false)
     {
         QFileInfo info(dirPath_+"/all_in_one.zip");
         if (info.exists()) { isExist=true; }
         LuaUtility::loadFile(L,dirPath_+"/all_in_one.zip","all_in_one.lua");
     }
     if (isExist==false) { return{}; }

     
     std::map<QString,QString> ans;
       

     return std::move(ans);
 }

 }
 }
