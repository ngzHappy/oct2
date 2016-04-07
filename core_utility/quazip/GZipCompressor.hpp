#ifndef pQCOMPRESSOR_Hgzip
#define pQCOMPRESSOR_Hgzip

#include "../core_utility_global.hpp"
#include <QtCore/qbytearray.h>
#include <memory>

namespace gzip {

class CORE_UTILITYSHARED_EXPORT QCompressor
{
private:

    static bool gzipCompress(QByteArray input, QByteArray &output, int level = -1);
    static bool gzipDecompress(QByteArray input, QByteArray &output);

    template<typename T>
    static QByteArray gzipDecompress(T && input){
        QByteArray ans ;
        if( gzipDecompress( std::forward<T>(input) ,ans ) ){
            return std::move(ans);
        }
        ans.clear();
        return ans ;
    }
public:
    static bool compressData(QByteArray input, QByteArray &output, int level = -1){
        return gzipCompress(std::move(input),output,level);
    }

    static bool decompressData(QByteArray input, QByteArray &output){
        return gzipDecompress(std::move(input),output);
    }

    template<typename T>
    static QByteArray decompressData(T && input){
        return gzipDecompress(std::forward<T>(input));
    }

    template<typename T>
    static QByteArray compressData(T && input,int level=-1){
        QByteArray ans__;
        if(gzipCompress(std::forward<T>(input),ans__,level)){
            return std::move(ans__);
        }
        ans__.clear();
        return std::move(ans__);
    }
};

}


#endif // QCOMPRESSOR_H

/*
 * endl of the file
*/
