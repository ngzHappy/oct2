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
    static bool compress(QByteArray input, QByteArray &output, int level = -1){
        return gzipCompress(std::move(input),output,level);
    }
    static bool decompress(QByteArray input, QByteArray &output){
        return gzipDecompress(std::move(input),output);
    }
    template<typename T>
    static QByteArray decompress(T && input){
        return gzipDecompress(std::forward<T>(input));
    }

};

}


#endif // QCOMPRESSOR_H

/*
 * endl of the file
*/
