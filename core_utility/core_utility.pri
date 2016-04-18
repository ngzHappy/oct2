include($$PWD/cplusplus_configure.pri)


INCLUDEPATH += $$PWD

#########################################
win32 :{
DEFINES += LOCAL_CODEC_=\\\"GBK\\\"
}else{
DEFINES += LOCAL_CODEC_=\\\"UTF-8\\\"
}

#########################################
win32{

win32-msvc*{

CONFIG(debug,debug|release){
OUTPWD= $$PWD/../binlib/msvc/bind
}else{
OUTPWD= $$PWD/../binlib/msvc/bin
}

}else{

CONFIG(debug,debug|release){
OUTPWD= $$PWD/../binlib/win32/bind
}else{
OUTPWD= $$PWD/../binlib/win32/bin
}

}

}else{

CONFIG(debug,debug|release){
OUTPWD= $$PWD/../binlib/common/bind
}else{
OUTPWD= $$PWD/../binlib/common/bin
}

}
#########################################





