
win32-g++{

##STRSAFE_NO_DEPRECATE
CONFIG(debug,debug|release){
LIBS += -lopencv_calib3d310d
LIBS += -lopencv_core310d
LIBS += -lopencv_features2d310d
LIBS += -lopencv_flann310d
LIBS += -lopencv_imgcodecs310d
LIBS += -lopencv_imgproc310d
LIBS += -lopencv_ml310d
LIBS += -lopencv_objdetect310d
LIBS += -lopencv_photo310d
LIBS += -lopencv_shape310d
LIBS += -lopencv_stitching310d
LIBS += -lopencv_superres310d
LIBS += -lopencv_ts310d
LIBS += -lopencv_video310d
LIBS += -lopencv_videoio310d
LIBS += -lopencv_videostab310d
LIBS += -lopencv_highgui310d
}else{
LIBS += -lopencv_calib3d310
LIBS += -lopencv_core310
LIBS += -lopencv_features2d310
LIBS += -lopencv_flann310
LIBS += -lopencv_imgcodecs310
LIBS += -lopencv_imgproc310
LIBS += -lopencv_ml310
LIBS += -lopencv_objdetect310
LIBS += -lopencv_photo310
LIBS += -lopencv_shape310
LIBS += -lopencv_stitching310
LIBS += -lopencv_superres310
LIBS += -lopencv_ts310
LIBS += -lopencv_video310
LIBS += -lopencv_videoio310
LIBS += -lopencv_videostab310
LIBS += -lopencv_highgui310
}

}##~win32-g++

win32-msvc*{

CONFIG(debug,debug|release){
LIBS += -lopencv_calib3d310d
LIBS += -lopencv_core310d
LIBS += -lopencv_features2d310d
LIBS += -lopencv_flann310d
LIBS += -lopencv_imgcodecs310d
LIBS += -lopencv_imgproc310d
LIBS += -lopencv_ml310d
LIBS += -lopencv_objdetect310d
LIBS += -lopencv_photo310d
LIBS += -lopencv_shape310d
LIBS += -lopencv_stitching310d
LIBS += -lopencv_superres310d
LIBS += -lopencv_ts310d
LIBS += -lopencv_video310d
LIBS += -lopencv_videoio310d
LIBS += -lopencv_videostab310d
LIBS += -lopencv_highgui310d
}else{
LIBS += -lopencv_calib3d310
LIBS += -lopencv_core310
LIBS += -lopencv_features2d310
LIBS += -lopencv_flann310
LIBS += -lopencv_imgcodecs310
LIBS += -lopencv_imgproc310
LIBS += -lopencv_ml310
LIBS += -lopencv_objdetect310
LIBS += -lopencv_photo310
LIBS += -lopencv_shape310
LIBS += -lopencv_stitching310
LIBS += -lopencv_superres310
LIBS += -lopencv_ts310
LIBS += -lopencv_video310
LIBS += -lopencv_videoio310
LIBS += -lopencv_videostab310
LIBS += -lopencv_highgui310
}

}##~win32-msvc*

linux-g++*{
#https://raw.githubusercontent.com/Itseez/opencv_3rdparty/81a676001ca8075ada498583e4166079e5744668/ippicv/ippicv_linux_20151201.tgz
CONFIG(debug,debug|release){
LIBS += -lopencv_calib3d
LIBS += -lopencv_core
LIBS += -lopencv_features2d
LIBS += -lopencv_flann
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_imgproc
LIBS += -lopencv_ml
LIBS += -lopencv_objdetect
LIBS += -lopencv_photo
LIBS += -lopencv_shape
LIBS += -lopencv_stitching
LIBS += -lopencv_superres
LIBS += -lopencv_ts
LIBS += -lopencv_video
LIBS += -lopencv_videoio
LIBS += -lopencv_videostab
LIBS += -lopencv_highgui
}else{
LIBS += -lopencv_calib3d
LIBS += -lopencv_core
LIBS += -lopencv_features2d
LIBS += -lopencv_flann
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_imgproc
LIBS += -lopencv_ml
LIBS += -lopencv_objdetect
LIBS += -lopencv_photo
LIBS += -lopencv_shape
LIBS += -lopencv_stitching
LIBS += -lopencv_superres
LIBS += -lopencv_ts
LIBS += -lopencv_video
LIBS += -lopencv_videoio
LIBS += -lopencv_videostab
LIBS += -lopencv_highgui
}

}##~linux-g++*


