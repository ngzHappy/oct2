#ifndef ARGVPACK_HPP
#define ARGVPACK_HPP

#include <string>
#include <memory>

class ArgvPack{
    class Data{
    public:
        std::string APPFileName;
        std::string subdirsProFileName;
        std::string outDirpath;
        std::string projectName;
    };
    std::shared_ptr<Data> data_;
public:
    ArgvPack(char ** argv):data_(new Data){
        setAPPFileName(argv[0]);
        setSubdirsProFileName(argv[1]);
        setOutDirpath(argv[2]);
        setProjectName(argv[3]);
    }
public:
    void setProjectName(const std::string& /*projectName*/);
    void setProjectName(std::string&& /*projectName*/);
    const std::string & getProjectName() const;
    const std::string & projectName() const{ return getProjectName();}
private: template<typename _t_PROJECTNAME_t__>
    void _p_setProjectName(_t_PROJECTNAME_t__ && /*projectName*/);
public:
    void setOutDirpath(const std::string& /*outDirpath*/);
    void setOutDirpath(std::string&& /*outDirpath*/);
    const std::string & getOutDirpath() const;
    const std::string & outDirpath() const{ return getOutDirpath();}
private: template<typename _t_OUTDIRPATH_t__>
    void _p_setOutDirpath(_t_OUTDIRPATH_t__ && /*outDirpath*/);
public:
    void setAPPFileName(const std::string& /*APPFileName*/);
    void setAPPFileName(std::string&& /*APPFileName*/);
    const std::string & getAPPFileName() const;
    const std::string & APPFileName() const{ return getAPPFileName();}
private: template<typename _t_APPFILENAME_t__>
    void _p_setAPPFileName(_t_APPFILENAME_t__ && /*APPFileName*/);
public:
    void setSubdirsProFileName(const std::string& /*subdirsProFileName*/);
    void setSubdirsProFileName(std::string&& /*subdirsProFileName*/);
    const std::string & getSubdirsProFileName() const;
    const std::string & subdirsProFileName() const{ return getSubdirsProFileName();}
private: template<typename _t_SUBDIRSPROFILENAME_t__>
    void _p_setSubdirsProFileName(_t_SUBDIRSPROFILENAME_t__ && /*subdirsProFileName*/);
};

#endif // ARGVPACK_HPP
