CONFIG += c++14

CONFIG(debug,debug|release){
DEFINES *= _DEBUG
}else{
DEFINES *= NDEBUG
}












