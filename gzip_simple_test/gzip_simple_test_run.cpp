/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/gzip_simple_test_run_exception.cpp"

extern void run(OpenCVWindow *  ) {

    QByteArray data_("abcdefg");
    QByteArray compress_data_ = gzip::QCompressor::compressData(data_);
    qDebug()<< gzip::QCompressor::decompressData(compress_data_);

}

