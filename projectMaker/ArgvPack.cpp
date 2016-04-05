#include "ArgvPack.hpp"

const std::string & ArgvPack::getAPPFileName() const{
    return data_->APPFileName;
}

template<typename _t_APPFILENAME_t__>
void ArgvPack::_p_setAPPFileName(_t_APPFILENAME_t__ &&_APPFileName_){
    data_->APPFileName=std::forward<_t_APPFILENAME_t__>(_APPFileName_);
}

void ArgvPack::setAPPFileName(const std::string&_APPFileName_){
    _p_setAPPFileName(_APPFileName_);
}

void ArgvPack::setAPPFileName(std::string&&_APPFileName_){
    _p_setAPPFileName(std::move(_APPFileName_));
}

const std::string & ArgvPack::getSubdirsProFileName() const{
    return data_->subdirsProFileName;
}

template<typename _t_SUBDIRSPROFILENAME_t__>
void ArgvPack::_p_setSubdirsProFileName(_t_SUBDIRSPROFILENAME_t__ &&_subdirsProFileName_){
    data_->subdirsProFileName=std::forward<_t_SUBDIRSPROFILENAME_t__>(_subdirsProFileName_);
}

void ArgvPack::setSubdirsProFileName(const std::string&_subdirsProFileName_){
    _p_setSubdirsProFileName(_subdirsProFileName_);
}

void ArgvPack::setSubdirsProFileName(std::string&&_subdirsProFileName_){
    _p_setSubdirsProFileName(std::move(_subdirsProFileName_));
}
const std::string & ArgvPack::getOutDirpath() const{
    return data_->outDirpath;
}

template<typename _t_OUTDIRPATH_t__>
void ArgvPack::_p_setOutDirpath(_t_OUTDIRPATH_t__ &&_outDirpath_){
    data_->outDirpath=std::forward<_t_OUTDIRPATH_t__>(_outDirpath_);
}

void ArgvPack::setOutDirpath(const std::string&_outDirpath_){
    _p_setOutDirpath(_outDirpath_);
}

void ArgvPack::setOutDirpath(std::string&&_outDirpath_){
    _p_setOutDirpath(std::move(_outDirpath_));
}

const std::string & ArgvPack::getProjectName() const{
    return data_->projectName;
}

template<typename _t_PROJECTNAME_t__>
void ArgvPack::_p_setProjectName(_t_PROJECTNAME_t__ &&_projectName_){
    data_->projectName=std::forward<_t_PROJECTNAME_t__>(_projectName_);
}

void ArgvPack::setProjectName(const std::string&_projectName_){
    _p_setProjectName(_projectName_);
}

void ArgvPack::setProjectName(std::string&&_projectName_){
    _p_setProjectName(std::move(_projectName_));
}
