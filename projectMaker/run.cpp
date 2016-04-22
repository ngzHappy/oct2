#include "ArgvPack.hpp"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>

#if defined(QT_CORE_LIB)
#include <QtCore/qdir.h>
#include <QtCore/qstring.h>
#endif

extern const char *_lua;
extern const char *_pro;
extern const char *_main_cpp;
extern const char *_MainWindow_cpp;
extern const char *_MainWindow_hpp_cpp;
extern const char *_OpenCVWindowDetail_cpp;
extern const char *_OpenCVWindowDetail_hpp_cpp;
extern const char *_run_cpp;
extern const char * _msvc_pre_build_hpp_cpp;
extern const char * _pre_build_hpp_cpp;
extern const char * _run_exception_cpp;

namespace {

void error(const std::string & e_) {
    std::cout<<e_<<std::endl;
}

std::string _get_sudirs_project_dir_(const ArgvPack & pack) {
    std::string sudirs_project_dir_;
    {
        auto pos_=pack.subdirsProFileName().find_last_of("/\\");
        if (pos_==std::string::npos) {
            error("format error :"+pack.subdirsProFileName());
            throw -1;
        }
        sudirs_project_dir_=std::string(
            pack.subdirsProFileName().begin(),
            pack.subdirsProFileName().begin()+pos_
            );
        if (sudirs_project_dir_.empty()) {
            error("format error :"+pack.subdirsProFileName());
            throw -1;
        }
    }
    return std::move(sudirs_project_dir_);
}

constexpr const char bom[3]{char(0x00ef),char(0x00bb),char(0x00bf)};
inline void write_bom(std::ofstream & ofs) {ofs.write(bom,3);}

inline void write_run_exception(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/private/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/private/";
    }

    {
        const std::string fileName=fileName_+pack.projectName()+"_run_exception.cpp";
        std::ofstream ofs(fileName,std::ios::out|std::ios::binary);
        if (ofs.is_open()==false) {
            error("error create file :"+fileName);
            throw -1;
        }
        write_bom(ofs);
        ofs<<_run_exception_cpp;
    }

}

inline void write_pre_build(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/private/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/private/";
    }

    {
        const std::string fileName=fileName_+"pre_build.hpp";
        std::ofstream ofs(fileName,std::ios::out|std::ios::binary);
        if (ofs.is_open()==false) {
            error("error create file :"+fileName);
            throw -1;
        }
        write_bom(ofs);
        ofs<<_pre_build_hpp_cpp;
    }

    {
        const std::string fileName=fileName_+"msvc_pre_build.hpp";
        std::ofstream ofs(fileName,std::ios::out|std::ios::binary);
        if (ofs.is_open()==false) {
            error("error create file :"+fileName);
            throw -1;
        }
        write_bom(ofs);
        ofs<<_msvc_pre_build_hpp_cpp;
    }
}

void write_lua(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/";
    }
    fileName_+=(pack.projectName()+".lua");
    std::ofstream ofs(fileName_,std::ios::out|std::ios::binary);
    if (ofs.is_open()==false) {
        error("error create file :"+fileName_);
        throw -1;
    }
    write_bom(ofs);
    ofs<<_lua;
}

void write_pro(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/";
    }
    fileName_+=(pack.projectName()+".pro");
    std::ofstream ofs(fileName_,std::ios::out|std::ios::binary);
    if (ofs.is_open()==false) {
        error("error create file :"+fileName_);
        throw -1;
    }

    std::string about_to_write_(_pro);
    {
        {
            const std::string replace_text_("_replace_first_window_replace_");
            about_to_write_.replace(
                about_to_write_.find(replace_text_),
                replace_text_.size(),
                ( pack.projectName() )
                );
        }
        {
            const std::string replace_text_("_replace_simple_pca_run__replace_");
            about_to_write_.replace(
                about_to_write_.find(replace_text_),
                replace_text_.size(),
                ( pack.projectName()+"_run_" )
                );
        }
        {
            const std::string replace_text_("$$PWD/_replace_run.cpp_replace_");
            about_to_write_.replace(
                about_to_write_.find(replace_text_),
                replace_text_.size(),
                ("$$PWD/"+pack.projectName()+"_run.cpp")
                );
        }
        {
            const std::string replace_text_("_replace_$$PWD/../core_utility/core_utility.pri_replace_");
            if (pack.outDirpath().empty()) {
                about_to_write_.replace(
                    about_to_write_.find(replace_text_),
                    replace_text_.size(),
                    std::string( "$$PWD/../core_utility/core_utility.pri" )
                    );
            }
            else {
                about_to_write_.replace(
                    about_to_write_.find(replace_text_),
                    replace_text_.size(),
                    std::string( "$$PWD/../../core_utility/core_utility.pri" )
                    );
            }
        }
        {
            const std::string replace_text_("_replace_$$PWD/../core_utility/opencv3.pri_replace_");
            if (pack.outDirpath().empty()) {
                about_to_write_.replace(
                    about_to_write_.find(replace_text_),
                    replace_text_.size(),
                    std::string( "$$PWD/../core_utility/opencv3.pri" )
                    );
            }
            else {
                about_to_write_.replace(
                    about_to_write_.find(replace_text_),
                    replace_text_.size(),
                    std::string( "$$PWD/../../core_utility/opencv3.pri" )
                    );
            }
        }
        {
            const std::string replace_text_("_replace_$$PWD/first_window.lua_replace_");
            about_to_write_.replace(
                about_to_write_.find(replace_text_),
                replace_text_.size(),
                ("$$PWD/"+pack.projectName()+".lua" )
                );
        }
    }
    ofs<<about_to_write_;
}

void write_main_cpp(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/";
    }
    fileName_+=("main.cpp");
    std::ofstream ofs(fileName_,std::ios::out|std::ios::binary);
    if (ofs.is_open()==false) {
        error("error create file :"+fileName_);
        throw -1;
    }
    {
        std::string about_to_write_(_main_cpp);
        {
            const std::string replace_text_("_replace_first_window.lua_replace_");
            about_to_write_.replace(
                about_to_write_.find(replace_text_),
                replace_text_.size(),
                (pack.projectName() /*the app will auto add .zip or .lua*/ )
                );
        }
        {
            const std::string replace_text_("_replace_project_name1_run__replace_");
            about_to_write_.replace(
                about_to_write_.find(replace_text_),
                replace_text_.size(),
                (pack.projectName() )
                );
        }
        {
            const std::string replace_text_("_replace_project_name_run__replace_");
            about_to_write_.replace(
                about_to_write_.find(replace_text_),
                replace_text_.size(),
                (pack.projectName() )
                );
        }
        {
            const std::string replace_text_("_replace_/../Images_replace_");
            if (pack.outDirpath().empty()) {
                about_to_write_.replace(
                    about_to_write_.find(replace_text_),
                    replace_text_.size(),
                    std::string("/../Images")
                    );
            }
            else {
                about_to_write_.replace(
                    about_to_write_.find(replace_text_),
                    replace_text_.size(),
                    std::string("/../../Images")
                    );
            }
        }
        write_bom(ofs);
        ofs<<about_to_write_;
    }
}

void write_MainWindow_cpp(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/";
    }
    fileName_+=("MainWindow.cpp");
    std::ofstream ofs(fileName_,std::ios::out|std::ios::binary);
    if (ofs.is_open()==false) {
        error("error create file :"+fileName_);
        throw -1;
    }
    write_bom(ofs);
    ofs<<_MainWindow_cpp;
}

void write_MainWindow_hpp_cpp(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/";
    }
    fileName_+=("MainWindow.hpp");
    std::ofstream ofs(fileName_,std::ios::out|std::ios::binary);
    if (ofs.is_open()==false) {
        error("error create file :"+fileName_);
        throw -1;
    }
    write_bom(ofs);
    ofs<<_MainWindow_hpp_cpp;
}

void write_OpenCVWindowDetail_cpp(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/";
    }
    fileName_+=("OpenCVWindowDetail.cpp");
    std::ofstream ofs(fileName_,std::ios::out|std::ios::binary);
    if (ofs.is_open()==false) {
        error("error create file :"+fileName_);
        throw -1;
    }
    write_bom(ofs);
    ofs<<_OpenCVWindowDetail_cpp;
}

void write_OpenCVWindowDetail_hpp_cpp(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/";
    }
    fileName_+=("OpenCVWindowDetail.hpp");
    std::ofstream ofs(fileName_,std::ios::out|std::ios::binary);
    if (ofs.is_open()==false) {
        error("error create file :"+fileName_);
        throw -1;
    }
    write_bom(ofs);
    ofs<<_OpenCVWindowDetail_hpp_cpp;
}

void write_run_cpp(const ArgvPack & pack) {
    std::string sudirs_project_dir_=_get_sudirs_project_dir_(pack);
    std::string fileName_;
    if (pack.outDirpath().empty()) {
        fileName_=sudirs_project_dir_+"/"+pack.projectName()+"/";
    }
    else {
        fileName_=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/";
    }
    fileName_+=(pack.projectName()+"_run.cpp");
    std::ofstream ofs(fileName_,std::ios::out|std::ios::binary);
    if (ofs.is_open()==false) {
        error("error create file :"+fileName_);
        throw -1;
    }
    std::string about_to_write_(_run_cpp);
    {
        const std::string replace_text_("_replace_simple_pca_run__replace_");
        about_to_write_.replace(
            about_to_write_.find(replace_text_),
            replace_text_.size(),
            ( pack.projectName()+"_run_" )
            );
    }
    {
        const std::string replace_text_("_replace_project_name_run__replace_");
        about_to_write_.replace(
            about_to_write_.find(replace_text_),
            replace_text_.size(),
            ( pack.projectName() )
            );
    }
    write_bom(ofs);
    ofs<<about_to_write_;
}

int tryMakeDir(const ArgvPack & pack) {
    {
        std::ofstream ofs(pack.subdirsProFileName(),std::ios::in);
        if (false==ofs.is_open()) {
            error("can not find :"+pack.subdirsProFileName());
            return -1;
        }
    }

    std::string sudirs_project_dir_;
    {
        auto pos_=pack.subdirsProFileName().find_last_of("/\\");
        if (pos_==std::string::npos) {
            error("format error :"+pack.subdirsProFileName());
            return -1;
        }
        sudirs_project_dir_=std::string(
            pack.subdirsProFileName().begin(),
            pack.subdirsProFileName().begin()+pos_
            );
        if (sudirs_project_dir_.empty()) {
            error("format error :"+pack.subdirsProFileName());
            return -1;
        }
    }

    std::list<std::string> try_make_dirs;
    std::string output_project_name;
    if (pack.outDirpath().empty()) {
        try_make_dirs.push_back(sudirs_project_dir_+"/"+pack.projectName());
        try_make_dirs.push_back(sudirs_project_dir_+"/"+pack.projectName()+"/private");
        output_project_name=sudirs_project_dir_+"/"+pack.projectName()
            +"/"+pack.projectName()+".pro";
    }
    else {
        try_make_dirs.push_back(sudirs_project_dir_+"/"+pack.outDirpath());
        try_make_dirs.push_back(sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName());
        try_make_dirs.push_back(sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()+"/private");
        output_project_name=sudirs_project_dir_+"/"+pack.outDirpath()+"/"+pack.projectName()
            +"/"+pack.projectName()+".pro";
    }

#if defined(QT_CORE_LIB)
    QDir var_dir_(QString::fromLocal8Bit(
        sudirs_project_dir_.c_str(),
        static_cast<std::int32_t>(sudirs_project_dir_.size())));
    for (const std::string & dir_:try_make_dirs) {
        QString dir_name_=QString::fromLocal8Bit(dir_.c_str(),
            static_cast<std::int32_t>(dir_.size()));
        var_dir_.mkdir(dir_name_);
    }
#else
#if defined(_WIN32)
    for (const std::string & dir_:try_make_dirs) {
        std::string command=std::string("mkdir ")+"\""+dir_+"\"";
        system(command.c_str());
    }
#else/*linux macx*/
    for (const std::string & dir_:try_make_dirs) {
        std::string command=std::string("mkdir ")+"\""+dir_+"\"";
        auto __ans=system(command.c_str());
        (void)__ans;
    }
#endif
#endif

    std::ofstream ofs(output_project_name,std::ios::out);
    if (ofs.is_open()==false) {
        error("make dir error!");
        return -1;
    }

    return 0;
}

}

int run( ArgvPack pack ){

    {
        const int try_make_dir_=tryMakeDir(pack);
        if (try_make_dir_) { return try_make_dir_; }
    }

    /*增加project*/
    {
        std::ofstream ofs(pack.subdirsProFileName(),std::ios::app);
        if (ofs.is_open()==false) {
            error("can not find :"+pack.subdirsProFileName());
            return -1;
        }

        ofs<<std::endl;
        ofs<<pack.projectName()<<".file = $$PWD/";
        if (pack.outDirpath().empty()) {
            ofs<<pack.projectName()<<"/"<<pack.projectName()<<".pro"<<std::endl;
        }
        else {
            ofs<<pack.outDirpath()<<"/";
            ofs<<pack.projectName()<<"/"<<pack.projectName()<<".pro"<<std::endl;
        }
        ofs<<pack.projectName()<<".depends += core_utility"<<std::endl;
        ofs<<"SUBDIRS += "<<pack.projectName();
        ofs<<std::endl;
    }

    try {
        write_lua(pack);
        write_pro(pack);
        write_main_cpp(pack);
        write_MainWindow_cpp(pack);
        write_MainWindow_hpp_cpp(pack);
        write_OpenCVWindowDetail_cpp(pack);
        write_OpenCVWindowDetail_hpp_cpp(pack);
        write_run_cpp(pack);
        write_pre_build(pack);
        write_run_exception(pack);
    }
    catch (const int & errorCode) {
        return errorCode;
    }

    return 0;
}


