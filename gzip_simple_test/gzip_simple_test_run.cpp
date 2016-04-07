/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>

extern void run(OpenCVWindow *  ) {

    QByteArray data_("abcdefg");
    compress_data_ = gzip::QCompressor::compressData(data_);
    qDebug()<< gzip::QCompressor::decompressData(compress_data_);

}

