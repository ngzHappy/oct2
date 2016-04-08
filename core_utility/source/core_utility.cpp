#include "core_utility.hpp"
#include <QtGui/qimage.h>
#include <QtCore/qdebug.h>

CoreUtility::CoreUtility(){

}

CoreUtility::~CoreUtility(){

}

/*
 * 程序启动时运行
*/
static void __private__init(){
    /*设置随机数种子*/
    std::srand(  int( std::time(nullptr) )  );
    /*强制载入图片插件*/
    {
        QImage * image_ = new QImage("null.png");
        delete image_;
    }
}

 Q_COREAPP_STARTUP_FUNCTION( __private__init )
