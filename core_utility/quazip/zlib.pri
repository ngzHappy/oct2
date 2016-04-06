wince: DEFINES += NO_ERRNO_H
INCLUDEPATH += $$PWD/3rd/zlib
SOURCES+= \
    $$PWD/3rd/zlib/zlib_adler32.c \
    $$PWD/3rd/zlib/zlib_compress.c \
    $$PWD/3rd/zlib/zlib_crc32.c \
    $$PWD/3rd/zlib/zlib_deflate.c \
    $$PWD/3rd/zlib/zlib_gzclose.c \
    $$PWD/3rd/zlib/zlib_gzlib.c \
    $$PWD/3rd/zlib/zlib_gzread.c \
    $$PWD/3rd/zlib/zlib_gzwrite.c \
    $$PWD/3rd/zlib/zlib_infback.c \
    $$PWD/3rd/zlib/zlib_inffast.c \
    $$PWD/3rd/zlib/zlib_inflate.c \
    $$PWD/3rd/zlib/zlib_inftrees.c \
    $$PWD/3rd/zlib/zlib_trees.c \
    $$PWD/3rd/zlib/zlib_uncompr.c \
    $$PWD/3rd/zlib/zlib_zutil.c


