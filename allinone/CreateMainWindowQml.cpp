#include "CreateMainWindowQml.hpp"
#include <QtWidgets/qapplication.h>
#include <QtCore/qresource.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qdir.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qfile.h>
#include <OpenCVUtility.hpp>
#include <list>
#include "MainWindow.hpp"

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

 namespace __private {
 static std::map<QString,QString> gen_old_configure();
 static std::map<QString,QString> gen_configure();
 static void save_AllInOneMainWindowQml(const std::list<std::pair<QString,QString>>&);
 static void write_AllInOneMainWindowQml(QFile &,const std::map<QString,QString>&);
 }

 void  CreateMainWindowQml::createAllInOneMainWindowQml(){
    QString varFileName=QDir::cleanPath(qApp->applicationDirPath()+"/AllInOneMainWindow.qml");
    QFile varFile(varFileName);
    varFile.open(QIODevice::WriteOnly|QIODevice::Text);

    auto configure=__private::gen_configure();
    {/*设置保存的arg*/
        const auto oldConfigure=__private::gen_old_configure();
        const auto eit=oldConfigure.end();
        for (auto & i:configure) {
            auto pos=oldConfigure.find(i.first);
            if (eit==pos) { continue; }
            i.second=pos->second;
        }
    }
    __private::write_AllInOneMainWindowQml(varFile,configure);
    varFile.flush();
 }

 CreateMainWindowQml::~CreateMainWindowQml()
 {

 }

 void MainWindow::_save() {
     int __i=0;
     QString key,value;
     std::list<std::pair<QString,QString>> ans;
     for (;;) {
         auto ___i=__i++;
         key=getProjectName(___i );
         value=getStartString(___i);
         if (key==value) {
             if (key=="@nil") { break; }
         }
         ans.emplace_back(std::move(key),std::move(value));
     }
     __private::save_AllInOneMainWindowQml(ans);
 }

 namespace __private {
 static void save_AllInOneMainWindowQml(const std::list<std::pair<QString,QString>>& data) {

     if ( data.empty()  ) {
         QuaZip zip(qApp->applicationDirPath()+"/all_in_one.zip");
         if (zip.open(QuaZip::mdCreate)) {
             QuaZipFile file(&zip);
             if (file.open(QIODevice::WriteOnly,QuaZipNewInfo("all_in_one.lua"))) {
                 file.write("--[[nullfile--]]\n");
             }
         }
         return;
     }

     auto __L= LuaUtility::createLuaState();
     auto L=__L.get();
     lua_createtable(L,data.size(),0);
     lua_pushvalue(L,-1);
     lua_setglobal(L,"app");
     const auto app_table=lua_gettop(L);

     int app_table_index=0;
     for(const auto & i:data){
         lua_createtable(L,2,0);
         const auto table_index=lua_gettop(L);
         lua_pushvalue(L,-1);
         lua_rawseti(L,app_table,++app_table_index);

         {
             const QByteArray data__=i.first.toLocal8Bit();
             lua_pushlstring(L,data__.constData(),data__.size());
             lua_rawseti(L,table_index,1);
         }

         {
             const QByteArray data__=i.second.toLocal8Bit();
             lua_pushlstring(L,data__.constData(),data__.size());
             lua_rawseti(L,table_index,2);
         }

         lua_settop(L,table_index-1);
     }

     lua_pushcfunction(L,&LuaUtility::tableToString);
     lua_pushstring(L,"app");
     lua_pushvalue(L,app_table);
     lua_pcall(L,2,LUA_MULTRET,-3);

     size_t len;
     auto * about_to_write=lua_tolstring(L,-1,&len);

     if (about_to_write) {
         QuaZip zip(qApp->applicationDirPath()+"/all_in_one.zip");
         if (zip.open(QuaZip::mdCreate)) {
             QuaZipFile file(&zip);
             if (file.open(QIODevice::WriteOnly,QuaZipNewInfo("all_in_one.lua"))) {
                 file.write(about_to_write,len);
             }
         }
     }
     else {
         QuaZip zip(qApp->applicationDirPath()+"/all_in_one.zip");
         if (zip.open(QuaZip::mdCreate)) {
             QuaZipFile file(&zip);
             if (file.open(QIODevice::WriteOnly,QuaZipNewInfo("all_in_one.lua"))) {
                 file.write("--[[nullfile--]]\n");
             }
         }
     }
 }
 }

 namespace __private {
 static void write_AllInOneMainWindowQml(
     QFile & file,
     const std::map<QString,QString>& configure) {
     QTextStream stream_(&file);
     stream_.setCodec(QTextCodec::codecForName("UTF-8"));

     stream_<<u8R"_!!_(/*qml main window*/
/*
此文件由程序生成
任何对于此文件的修改都是无效的
*/
import QtQuick 2.5
import QtQml.Models 2.2

/*rootWindow*/

Rectangle {
    width: 1000;
    height: 1000;
    color: Qt.rgba(0.5,0.6,0.5,1);
    id : rootItem;

    function getProjectName(n){
        if(n>=itemModel.count){return "@nil";}
        return itemModel.get(n).projectName;
    }
    function getStartString(n){
        if(n>=itemModel.count){return "@nil";}
        return itemModel.get(n).startString;
    }

    ObjectModel {
        id: itemModel;
        /****************************************/
)_!!_"_qs;

     for(const auto & i:configure){
         /*AllInOneItem{projectName:"0";startString:"";width: rootItem.width;}*/
         stream_<<"AllInOneItem{projectName:";
         stream_<<u8R"(")"<<i.first<<u8R"(";)";
         stream_<<"startString:";
         stream_<<u8R"(")"<<i.second<<u8R"(";width: rootItem.width;})";
         stream_<<endl;
     }

     stream_<<u8R"_11_(
    /****************************************/
    }
    ListView {
        anchors.fill: parent;
        model: itemModel;
    }

         }


)_11_"_qs;

 }
 }

 namespace __private {
 static std::map<QString,QString> gen_configure() {
     std::map<QString,QString> ans_;

     QDir dir(qApp->applicationDirPath());

     const QString app_name_{APP_NAME_};
     const QString arg_;
     dir.setFilter(QDir::Executable|QDir::Files);
     auto info=dir.entryInfoList();
     for (const auto & i:info) {
         /*name??? 因为有后缀,这里不跨平台 */
         QString name_ = i.completeBaseName();
         if (name_==app_name_) { continue; }
#if defined(Q_OS_WIN32)
#else
         if (name_.startsWith("libcore_utilityd.so")) { continue; }
         if (name_.startsWith("libcore_utility.so")) { continue; }
#endif
         /*on windows it's ???.exe ???.bat ...but on linux it will be ??? */
         name_=i.fileName();
         ans_.insert({ std::move(name_),arg_ });
     }

     return std::move(ans_);
 }
 }

 namespace __private {
 /*
 app={
 {"xxx","-l xvsdf"},
 {"yyy","-l xvsdf"},
 }
 */
 static std::map<QString,QString> gen_old_configure() {
     /*all_in_one.lua;*/
     /*all_in_one.zip;*/
     QString dirPath_ = QDir::cleanPath( qApp->applicationDirPath());
     auto _LuaState_= LuaUtility::createLuaState();
     auto * L=_LuaState_.get();

     bool isExist=false;
     {
         QFileInfo info(dirPath_+"/all_in_one.zip");
         if (info.exists()) {
             isExist=
                 LuaUtility::loadFile(L,dirPath_+"/all_in_one.zip","all_in_one.lua")>0;
         }
     }
     if(isExist==false){
         QFileInfo info(dirPath_+"/all_in_one.lua");
         if (info.exists()) {
             isExist=
                 LuaUtility::loadFile(L,dirPath_+"/all_in_one.lua","all_in_one.lua")>0;
         }
     }

     if (isExist==false) { return{}; }

     if (0==lua_pcall(L,0,LUA_MULTRET,-1)) {
         std::map<QString,QString> ans;
         luaL_dostring(L,"return app");
         if (lua_istable(L,-1)==false) { return{}; }

         const auto table_=lua_gettop(L);
         lua_pushnil(L);
         while (lua_next(L,table_)) {
             if (lua_istable(L,-1)) {
                 auto table_kv=lua_gettop(L);
                 QString key,value;
                 lua_rawgeti(L,table_kv,1);
                 {
                     size_t len;
                     auto *str=luaL_tolstring(L,-1,&len);
                     if (str==nullptr) { lua_settop(L,table_kv-1); continue; }
                     key=QString::fromUtf8(str,len);
                 }
                 lua_rawgeti(L,table_kv,2);
                 {
                     size_t len;
                     auto *str=luaL_tolstring(L,-1,&len);
                     if (str==nullptr) { lua_settop(L,table_kv-1); continue; }
                     value=QString::fromUtf8(str,len);
                 }
                 lua_settop(L,table_kv-1);
                 ans.insert({std::move(key),std::move(value)});
             }
             else {
                 lua_pop(L,1);
             }
         }

         return std::move(ans);
     }

     return{};
 }

 }

