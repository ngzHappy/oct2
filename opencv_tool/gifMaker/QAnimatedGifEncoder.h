#ifndef __QAnimatedGifEncoder__H__
#define __QAnimatedGifEncoder__H__

#include <memory>
#include <cstdint>
#include <cstddef>
#include <QtGui/qimage.h>
#include <cstdbool>
#include <ciso646>
#include <functional>
#include <QtCore/qstring.h>
#include <QtCore/qiodevice.h>

namespace mgui {
//java like
typedef bool Boolean;
typedef char16_t Char;
typedef char Byte;/*there must be char not unsigned char or signed char*/
typedef std::int16_t Short;
typedef std::int32_t Integer;
typedef std::int64_t Long;
typedef float Float;
typedef double Double;
typedef class Void {} Void;
typedef QIODevice OutputStream;
typedef QImage BufferedImage;//BufferedImage 应当提供隐式数据共享
typedef QRgb Color;
typedef QString String;

/**
    * Class AnimatedGifEncoder - Encodes a GIF file consisting of one or
    * more frames.
    * <pre>
    * Example:
    *    AnimatedGifEncoder e = new AnimatedGifEncoder();
    *    e.start(outputFileName);
    *    e.setDelay(1000);   // 1 frame per sec
    *    e.addFrame(image1);
    *    e.addFrame(image2);
    *    e.finish();
    * </pre>
    * No copyright asserted on the source code of this class.  May be used
    * for any purpose, however, refer to the Unisys LZW patent for restrictions
    * on use of the associated LZWEncoder class.  Please forward any corrections
    * to kweiner@fmsware.com.
    *
    * @author Kevin Weiner, FM Software
    * @version 1.03 November 2003
    *
    */

class QAnimatedGifEncoder {
    class ThisData;
    friend class ThisData;
    std::unique_ptr<ThisData,std::function<void(ThisData *)>> thisData;/**/
    static_assert(sizeof(Double)==8,"Double should be 64 bit");
    static_assert(sizeof(Float)==4,"Float should be 32 bit");
public:
    QAnimatedGifEncoder();
    ~QAnimatedGifEncoder();

    /**
        * Sets the delay time between each frame, or changes it
        * for subsequent frames (applies to last frame added).
        *
        * @param ms int delay time in milliseconds
        */
    void setDelay(const Integer ms);

    /**
        * Sets the GIF frame disposal code for the last added frame
        * and any subsequent frames.  Default is 0 if no transparent
        * color has been set, otherwise 2.
        * @param code int disposal code.
        */
    void setDispose(const Integer code);

    /**
        * Sets the number of times the set of GIF frames
        * should be played.  Default is 1; 0 means play
        * indefinitely.  Must be invoked before the first
        * image is added.
        *
        * @param iter int number of iterations.
        * @return
        */
    void setRepeat(const Integer iter);

    /**
        * Sets the transparent color for the last added frame
        * and any subsequent frames.
        * Since all colors are subject to modification
        * in the quantization process, the color in the final
        * palette for each frame closest to the given color
        * becomes the transparent color for that frame.
        * May be set to null to indicate no transparent color.
        *
        * @param c Color to be treated as transparent on display.
        */
    void setTransparent(const Color c);

    /**
        * Sets frame rate in frames per second.  Equivalent to
        * <code>setDelay(1000/fps)</code>.
        *
        * @param fps float frame rate (frames per second)
        */
    void setFrameRate(const Float fps);

    /**
        * Sets quality of color quantization (conversion of images
        * to the maximum 256 colors allowed by the GIF specification).
        * Lower values (minimum = 1) produce better colors, but slow
        * processing significantly.  10 is the default, and produces
        * good color mapping at reasonable speeds.  Values greater
        * than 20 do not yield significant improvements in speed.
        *
        * @param quality int greater than 0.
        * @return
        */
    void setQuality(const Integer quality);

    /**
        * Adds next GIF frame.  The frame is not written immediately, but is
        * actually deferred until the next frame is received so that timing
        * data can be inserted.  Invoking <code>finish()</code> flushes all
        * frames.  If <code>setSize</code> was not invoked, the size of the
        * first image is used for all subsequent frames.
        *
        * @param im BufferedImage containing frame to write.
        * @return true if successful.
        */
    Boolean addFrame(const BufferedImage &im);
    Boolean addFrame(BufferedImage && im);

    /**
        * Sets the GIF frame size.  The default size is the
        * size of the first frame added if this method is
        * not invoked.
        *
        * @param w int frame width.
        * @param h int frame width.
        */
    void setSize(const Integer w,const Integer h);

    /**
        * Flushes any pending data and closes output file.
        * If writing to an OutputStream, the stream is not
        * closed.
        */
    Boolean finish();

    /**
        * Initiates GIF file creation on the given stream.  The stream
        * is not closed automatically.
        * std::ios::binary must
        *
        * @param os OutputStream on which GIF images are written.
        * @return false if initial write failed.
        */
    Boolean start(OutputStream & os);

protected:
private:
    void writeString(const String & s);
    void analyzePixels();
    void getImagePixels();
    Integer findClosest(Color c);
    void writeGraphicCtrlExt();
    void writeShort(Integer value);
    void writePixels();
    void writePalette();
    void writeNetscapeExt();
    void writeLSD();
    void writeImageDesc();
};//~class

}
#endif

