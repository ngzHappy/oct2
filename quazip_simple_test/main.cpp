#include <QtWidgets/qapplication.h>
#include <QtWidgets/qwidget.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qtextcodec.h>
#include <QtCore/qdir.h>
#include <QtCore/qfile.h>
#include <quazip/quazip.h>
#include <quazip/quazipfile.h>
#include <quazip/quazipfileinfo.h>
#include <core_utility.hpp>
#include <exception>

int main(int argc, char *argv[])try
{
    /*设置本地编码*/
    QTextCodec::setCodecForLocale( QTextCodec::codecForName(LOCAL_CODEC_) );
    QApplication app(argc, argv);

    QWidget * widget = new QWidget;
    widget->setAttribute( Qt::WA_DeleteOnClose );
    widget->show();

    QString dir_string_ = QDir::cleanPath( app.applicationDirPath() ) ;

#define SIMPLE_QUAZIP_TEST "simple_quazip_test"

    /*创建目录*/
    {
        QDir dir( dir_string_ );
        dir.mkdir(SIMPLE_QUAZIP_TEST);
        dir.cd(SIMPLE_QUAZIP_TEST);
        dir.mkdir(SIMPLE_QUAZIP_TEST);
    }

    dir_string_+="/"/**/SIMPLE_QUAZIP_TEST;

    /*创建测试文件*/
    {
        QFile file_(dir_string_+"/file1.txt");
        file_.open(QFile::WriteOnly|QFile::Text);
        QTextStream stream_(&file_);
        stream_<<"file1"<<endl;
    }

    {
        QFile file_(dir_string_+"/file2.txt");
        file_.open(QFile::WriteOnly|QFile::Text);
        QTextStream stream_(&file_);
        stream_<<"file2"<<endl;
    }

    {
        QFile file_(dir_string_+"/file3.txt");
        file_.open(QFile::WriteOnly|QFile::Text);
        QTextStream stream_(&file_);
        stream_<<"file3"<<endl;
    }

    /*压缩*/
    {
        QuaZip zip(dir_string_+"/file.zip");
        zip.setFileNameCodec("UTF-8");
        zip.open(QuaZip::mdCreate);

        QStringList files{ "file1.txt","file2.txt","file3.txt" };

        for(const QString & file_name_ : files)
        {
            QFile file_(dir_string_+"/"+file_name_);
            file_.open(QFile::ReadOnly );

            QuaZipFile outFile(&zip);
            QuaZipNewInfo info(file_name_);
            info.setPermissions(QFileDevice::ReadOwner|
                                QFileDevice::WriteOwner|
                                QFileDevice::ExeOwner|
                                QFileDevice::ReadUser|
                                QFileDevice::WriteUser|
                                QFileDevice::ExeUser|
                                QFileDevice::ReadGroup|
                                QFileDevice::WriteGroup|
                                QFileDevice::ExeGroup|
                                QFileDevice::ReadOther|
                                QFileDevice::WriteOther|
                                QFileDevice::ExeOther);
            outFile.open(QIODevice::WriteOnly,info );

            outFile.write( file_.readAll() );

        }
    }

    /*解压缩*/
    {
        QuaZip zip(dir_string_+"/file.zip");
        zip.open(QuaZip::mdUnzip);

        for(bool flag_ = zip.goToFirstFile() ; flag_ ;flag_=zip.goToNextFile()){
            QString file_name_ = dir_string_ + "/"
                    +SIMPLE_QUAZIP_TEST "/"+zip.getCurrentFileName() ;
            QuaZipFile zFile(&zip );
            zFile.open( QIODevice::ReadOnly );
            QFile file_( file_name_ );
            file_.open( QIODevice::WriteOnly );
            file_.write( zFile.readAll() );
        }

    }

    return app.exec();

}
catch (const std::exception & e) {
    std::cout<<e.what()<<std::endl;
    return -10;
}
catch (...) {
    std::cout<<"unknow exception @ main"<<std::endl;
    return -99999;
}



