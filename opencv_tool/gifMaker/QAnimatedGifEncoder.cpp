#include "QAnimatedGifEncoder.h"

#include<cmath>
#include<QVector>
#include<vector>
#include<utility>
#include<algorithm>
#include<QPainter>
#include<array>

#ifndef null
#define null 0
#endif

#ifndef one
#define one (Integer(1))
#endif

namespace mgui {

template<typename T1,typename T>
static inline void writeSome(const T1 & some,T * out) {
    out->write((Byte *)(&some),sizeof(T1));
}

template<typename T>
static inline void writeSome(Integer some,T * out) {
    out->write((Byte *)(&some),sizeof(Integer));
}

template<typename T>
static inline void writeSome(Byte some,T * out) {
    out->write(&some,sizeof(Byte));
}

}

namespace mgui
{
#ifdef _DEBUG
typedef std::vector<Byte> PixType;
#else
//隐式数据共享
typedef  QVector<Byte>  PixType;
#endif

class QuantizationAlgorithm {
public:
    QuantizationAlgorithm() {}
    virtual void construct(const PixType & /*thepic*/,Integer /*len*/,Integer /*sample*/)=0;
    virtual ~QuantizationAlgorithm() {}
    virtual QVector<Byte> process()=0;
    virtual Integer map(Integer b,Integer g,Integer r)=0;
};

/* NeuQuant Neural-Net Quantization Algorithm
    * ------------------------------------------
    *
    * Copyright (c) 1994 Anthony Dekker
    *
    * NEUQUANT Neural-Net quantization algorithm by Anthony Dekker, 1994.
    * See "Kohonen neural networks for optimal colour quantization"
    * in "Network: Computation in Neural Systems" Vol. 5 (1994) pp 351-367.
    * for a discussion of the algorithm.
    *
    * Any party obtaining a copy of these files from the author, directly or
    * indirectly, is granted, free of charge, a full and unrestricted irrevocable,
    * world-wide, paid up, royalty-free, nonexclusive right and license to deal
    * in this software and documentation files (the "Software"), including without
    * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
    * and/or sell copies of the Software, and to permit persons who receive
    * copies from any such party to do so, with the only requirement being
    * that this copyright notice remain intact.
    */
    // Ported to Java 12/00 K Weiner

class NeuQuant :public QuantizationAlgorithm {
public:

    NeuQuant() {
        static_assert(one==1,"one must equal 1");
        static_assert(null==false,"null must equal false");
    }

    enum :Integer {
        netsize=256,
        prime1=499,
        prime2=491,
        prime3=487,
        prime4=503,
        minpicturebytes=(3*prime4),
        maxnetpos=(netsize-1),
        netbiasshift=4,
        ncycles=100,
        intbiasshift=16,
        intbias=(one<<intbiasshift),
        gammashift=10,
        gamma=(one<<gammashift),
        betashift=10,
        beta=(intbias>>betashift),
        betagamma=(intbias<<(gammashift-betashift)),
        initrad=(netsize>>3),
        radiusbiasshift=6,
        radiusbias=(one<<radiusbiasshift),
        initradius=(initrad * radiusbias),
        radiusdec=30,
        alphabiasshift=10,
        initalpha=(one<<alphabiasshift),
        radbiasshift=8,
        radbias=(one<<radbiasshift),
        alpharadbshift=(alphabiasshift+radbiasshift),
        alpharadbias=(one<<alpharadbshift),
    };

    Integer alphadec;
    PixType thepicture;
    Integer lengthcount=0;
    Integer samplefac=0;
    QVector<std::array<Integer,4>> network;
    std::array<Integer,256> netindex;
    std::array<Integer,netsize> bias;
    std::array<Integer,netsize> freq;
    std::array<Integer,initrad> radpower;

    NeuQuant(const PixType & thepic,Integer len,Integer sample):
        NeuQuant() {
        thepicture=thepic;
        _init_(len,sample);
    }

    NeuQuant(PixType && thepic,Integer len,Integer sample):
        NeuQuant() {
        thepicture=std::move(thepic);
        _init_(len,sample);
    }

    virtual void construct(const PixType & thepic,Integer len,Integer sample)override {
        thepicture=std::move(thepic);
        _init_(len,sample);
    }

    QVector<Byte> colorMap() {
        QVector<Byte> map;
        map.resize(3*netsize);
        QVector<Integer> index;
        index.resize(netsize);
        for (Integer i=0; i<netsize; ++i)
            index[network[i][3]]=i;

        Integer k=0;

        for (Integer i=0; i<netsize; ++i) {
            Integer j=index[i];
            map[k++]=(Byte)(network[j][0]&0x00ff);
            map[k++]=(Byte)(network[j][1]&0x00ff);
            map[k++]=(Byte)(network[j][2]&0x00ff);
        }

        return std::move(map);
    }

    void inxbuild() {//std::vector<Integer>
        Integer i=0;
        Integer j=0;
        Integer smallpos=0;
        Integer smallval=0;
        Integer previouscol=0;
        Integer startpos=0;
        for (i=0; i<netsize; ++i) {
            auto & p=network[i];
            smallpos=i;
            smallval=p[1]; /* index on g */
            for (j=i+1; j<netsize; ++j) {
                auto & q=network[j];
                if (q[1]<smallval) { /* index on g */
                    smallpos=j;
                    smallval=q[1]; /* index on g */
                }
            }
            auto & q=network[smallpos];
            if (i!=smallpos) {
                j=q[0];
                q[0]=p[0];
                p[0]=j;
                j=q[1];
                q[1]=p[1];
                p[1]=j;
                j=q[2];
                q[2]=p[2];
                p[2]=j;
                j=q[3];
                q[3]=p[3];
                p[3]=j;
            }

            if (smallval!=previouscol) {
                netindex[previouscol]=(startpos+i)>>1;
                for (j=previouscol+1; j<smallval; ++j)
                    netindex[j]=i;
                previouscol=smallval;
                startpos=i;
            }
        }//~for i
        netindex[previouscol]=(startpos+maxnetpos)>>1;
        for (j=previouscol+1; j<256; ++j)
            netindex[j]=maxnetpos; /* really 256 */
    }//~void inxbuild()

    //altersingle
    void alterneigh(Integer rad,Integer i,Integer b,Integer g,Integer r) {
        Integer j,k,lo,hi,a,m;
        lo=i-rad;
        if (lo<-1)
            lo=-1;
        hi=i+rad;
        if (hi>netsize)
            hi=netsize;
        j=i+1;
        k=i-1;
        m=1;

        while ((j<hi)||(k>lo)) {
            a=radpower[m++];
            if (j<hi) {
                auto & p=network[j++];
                p[0]-=(a * (p[0]-b))/alpharadbias;
                p[1]-=(a * (p[1]-g))/alpharadbias;
                p[2]-=(a * (p[2]-r))/alpharadbias;
            }
            if (k>lo) {
                auto &p=network[k--];
                p[0]-=(a * (p[0]-b))/alpharadbias;
                p[1]-=(a * (p[1]-g))/alpharadbias;
                p[2]-=(a * (p[2]-r))/alpharadbias;
            }
        }

    }

    void altersingle(Integer alpha,Integer i,Integer b,Integer g,Integer r) {
        /* alter hit neuron */
        auto & n=network[i];
        n[0]-=(alpha * (n[0]-b))/initalpha;
        n[1]-=(alpha * (n[1]-g))/initalpha;
        n[2]-=(alpha * (n[2]-r))/initalpha;
    }

    /* Search for biased BGR values
        ---------------------------- */
    Integer contest(Integer b,Integer g,Integer r) {
        /* finds closest neuron (min dist) and updates freq */
        /* finds best neuron (min dist-bias) and returns position */
        /* for frequently chosen neurons, freq[i] is high and bias[i] is negative */
        /* bias[i] = gamma*((1/netsize)-freq[i]) */
        Integer i,dist,a,biasdist,betafreq;
        Integer bestpos,bestbiaspos,bestd,bestbiasd;
        //int[] n;
        bestd=~(((int)1)<<31);
        bestbiasd=bestd;
        bestpos=-1;
        bestbiaspos=bestpos;
        for (i=0; i<netsize; ++i) {
            auto & n=network[i];
            dist=n[0]-b;
            if (dist<0)
                dist=-dist;
            a=n[1]-g;
            if (a<0)
                a=-a;
            dist+=a;
            a=n[2]-r;
            if (a<0)
                a=-a;
            dist+=a;
            if (dist<bestd) {
                bestd=dist;
                bestpos=i;
            }
            biasdist=dist-((bias[i])>>(intbiasshift-netbiasshift));
            if (biasdist<bestbiasd) {
                bestbiasd=biasdist;
                bestbiaspos=i;
            }
            betafreq=(freq[i]>>betashift);
            freq[i]-=betafreq;
            bias[i]+=(betafreq<<gammashift);
        }
        freq[bestpos]+=beta;
        bias[bestpos]-=betagamma;
        return (bestbiaspos);
    }

    void learn() {
        Integer i,j,b,g,r;
        Integer radius,rad,alpha,step,delta,samplepixels;
        //std::vector<Byte> & p;
        Integer pix,lim;
        if (lengthcount<minpicturebytes)
            samplefac=1;
        alphadec=30+((samplefac-1)/3);
        auto & p=thepicture;
        pix=0;
        lim=lengthcount;
        samplepixels=lengthcount/(3*samplefac);
        delta=samplepixels/ncycles;
        alpha=initalpha;
        radius=initradius;

        rad=radius>>radiusbiasshift;
        if (rad<=1)
            rad=0;
        for (i=0; i<rad; ++i)
            radpower[i]=
            alpha * (((rad * rad-i * i) * radbias)/(rad * rad));

        if (lengthcount<minpicturebytes)
            step=3;
        else if ((lengthcount % prime1)!=0)
            step=3*prime1;
        else {
            if ((lengthcount % prime2)!=0)
                step=3*prime2;
            else {
                if ((lengthcount % prime3)!=0)
                    step=3*prime3;
                else
                    step=3*prime4;
            }
        }

        i=0;
        while (i<samplepixels) {
            b=(p[pix+0]&0xff)<<netbiasshift;
            g=(p[pix+1]&0xff)<<netbiasshift;
            r=(p[pix+2]&0xff)<<netbiasshift;
            j=contest(b,g,r);
            altersingle(alpha,j,b,g,r);
            if (rad!=0)
                alterneigh(rad,j,b,g,r); /* alter neighbours */
            pix+=step;
            if (pix>=lim)
                pix-=lengthcount;
            ++i;
            if (delta==0)
                delta=1;
            if (i % delta==0) {
                alpha-=alpha/alphadec;
                radius-=radius/radiusdec;
                rad=radius>>radiusbiasshift;
                if (rad<=1)
                    rad=0;
                for (j=0; j<rad; ++j)
                    radpower[j]=
                    alpha * (((rad * rad-j * j) * radbias)/(rad * rad));
            }
        }

    }//~learn

    void unbiasnet() {
        Integer i;
        for (i=0; i<netsize; ++i) {
            network[i][0]>>=netbiasshift;
            network[i][1]>>=netbiasshift;
            network[i][2]>>=netbiasshift;
            network[i][3]=i; /* record colour no */
        }
    }

    QVector<Byte> process() {
        learn();
        unbiasnet();
        inxbuild();
        return std::move(colorMap());
    }

    Integer map(
            Integer b,
            Integer g,
            Integer r
    ) {
        Integer i,j,dist,a,bestd;
        Integer best;

        bestd=1000; /* biggest possible dist is 256*3 */
        best=-1;
        i=netindex[g]; /* index on g */
        j=i-1; /* start at netindex[g] and work outwards */

        while ((i<netsize)||(j>=0)) {
            if (i<netsize) {
                auto &p=network[i];
                dist=p[1]-g; /* inx key */
                if (dist>=bestd)
                    i=netsize; /* stop iter */
                else {
                    ++i;
                    if (dist<0)
                        dist=-dist;
                    a=p[0]-b;
                    if (a<0)
                        a=-a;
                    dist+=a;
                    if (dist<bestd) {
                        a=p[2]-r;
                        if (a<0)
                            a=-a;
                        dist+=a;
                        if (dist<bestd) {
                            bestd=dist;
                            best=p[3];
                        }
                    }
                }
            }
            if (j>=0) {
                auto &p=network[j];
                dist=g-p[1]; /* inx key - reverse dif */
                if (dist>=bestd)
                    j=-1; /* stop iter */
                else {
                    j--;
                    if (dist<0)
                        dist=-dist;
                    a=p[0]-b;
                    if (a<0)
                        a=-a;
                    dist+=a;
                    if (dist<bestd) {
                        a=p[2]-r;
                        if (a<0)
                            a=-a;
                        dist+=a;
                        if (dist<bestd) {
                            bestd=dist;
                            best=p[3];
                        }
                    }
                }
            }

        }//~while
        return (best);
    }
private:
    void _init_(Integer len,Integer sample) {
        Integer i;

        lengthcount=len;
        samplefac=sample;

        network.resize(netsize);

        for (i=0; i<netsize; ++i) {
            const static std::array<Integer,4> var_data_temp={ 0, 0, 0, 0 };
            network[i]=var_data_temp;
            auto & p=network[i];
            const auto var_temp=(i<<(netbiasshift+8))/netsize;
            p[0]=var_temp;
            p[1]=var_temp;
            p[2]=var_temp;
            freq[i]=intbias/netsize; /* 1/netsize */
            bias[i]=0;
        }
    }
}; //~class NeuQuant


}

namespace mgui {
class LZWEncoder {
public:
#ifndef EOF
    static const Integer EOF; /*= -1*/
#endif
    enum :Integer {
        BITS=12,
        HSIZE=5003
    };

    std::array<Integer,HSIZE> htab;
    std::array<Integer,HSIZE> codetab;
    std::array<Byte,256> accum;

    Integer imgW=0;
    Integer imgH=0;
    QVector<Byte> pixAry;
    Integer initCodeSize=0;
    Integer remaining=0;
    Integer curPixel=0;
    Integer n_bits=0; // number of bits/code
    Integer maxbits=BITS; // user settable max # bits/code
    Integer maxcode=0; // maximum code, given n_bits
    Integer maxmaxcode=(1<<BITS); // should NEVER generate this code
    Integer hsize=HSIZE; // for dynamic table sizing
    Integer free_ent=0; // first unused entry
    Boolean clear_flg=false;
    Integer g_init_bits=0;
    Integer ClearCode=0;
    Integer EOFCode=0;
    Integer cur_accum=0;
    Integer cur_bits=0;
    static const std::array<Integer,17> masks;// =
    Integer a_count=0;

    LZWEncoder() {
    }

    //----------------------------------------------------------------------------
    LZWEncoder(
            Integer width,
            Integer height,
            const QVector<Byte> & pixels,
            Integer color_depth):LZWEncoder() {
        imgW=width;
        imgH=height;
        pixAry=pixels;
        initCodeSize=(std::max)(2,color_depth);
    }

    void char_out(Byte c,OutputStream * outs) {
        accum[a_count++]=c;
        if (a_count>=254)
            flush_char(outs);
    }

    //// Clear out the hash table
    //// table clear for block compress
    void cl_block(OutputStream * outs) {
        cl_hash(hsize);
        free_ent=ClearCode+2;
        clear_flg=true;
        output(ClearCode,outs);
    }

    //// reset code table
    void cl_hash(const Integer hsize) {
        for (Integer i=0; i<hsize; ++i)
            htab[i]=-1;
    }

    void compress(Integer init_bits,OutputStream *outs) {
        Integer fcode=0;
        Integer i=0;
        Integer c=0;
        Integer ent=0;
        Integer disp=0;
        Integer hsize_reg=0;
        Integer hshift=0;
        // Set up the globals:  g_init_bits - initial number of bits
        g_init_bits=init_bits;
        // Set up the necessary values
        clear_flg=false;
        n_bits=g_init_bits;
        maxcode=MAXCODE(n_bits);
        ClearCode=1<<(init_bits-1);
        EOFCode=ClearCode+1;
        free_ent=ClearCode+2;
        a_count=0; // clear packet
        ent=nextPixel();
        hshift=0;
        for (fcode=hsize; fcode<65536; fcode*=2)
            ++hshift;
        hshift=8-hshift; // set hash code range bound
        hsize_reg=hsize;
        cl_hash(hsize_reg); // clear hash table
        output(ClearCode,outs);
    outer_loop: while ((c=nextPixel())!=EOF) {
        fcode=(c<<maxbits)+ent;
        i=(c<<hshift)^ent; // xor hashing
        if (htab[i]==fcode) {
            ent=codetab[i];
            continue;
        }
        else if (htab[i]>=0) // non-empty slot
        {
            disp=hsize_reg-i; // secondary hash (after G. Knott)
            if (i==0)
                disp=1;
            do {
                if ((i-=disp)<0)
                    i+=hsize_reg;
                if (htab[i]==fcode) {
                    ent=codetab[i];
                    goto outer_loop;
                }
            } while (htab[i]>=0);
        }
        output(ent,outs);
        ent=c;
        if (free_ent<maxmaxcode) {
            codetab[i]=free_ent++; // code -> hashtable
            htab[i]=fcode;
        }
        else
            cl_block(outs);
    }
                // Put out the final code.
                output(ent,outs);
                output(EOFCode,outs);
    }

    //----------------------------------------------------------------------------
    void encode(OutputStream * os) {
        os->put(initCodeSize&0x00ff); // write "initial code size" byte
        remaining=imgW * imgH; // reset navigation variables
        curPixel=0;
        compress(initCodeSize+1,os); // compress and write the pixel data
        os->put(0);
    }

    //// Flush the packet to disk, and reset the accumulator
    void flush_char(OutputStream * outs) {
        if (a_count>0) {
            outs->put(0x00ff&a_count);
            outs->write(accum.data(),a_count);
            a_count=0;
        }
    }

    static inline Integer MAXCODE(Integer n_bits) {
        return (1<<n_bits)-1;
    }

    //----------------------------------------------------------------------------
    // Return the next pixel from the image
    //----------------------------------------------------------------------------
    Integer nextPixel() {
        if (remaining==0)
            return EOF;
        --remaining;
        Byte pix=pixAry[curPixel++];
        return pix&0x00ff;
    }

    void output(Integer code,OutputStream * outs) {
        cur_accum&=masks[cur_bits];
        if (cur_bits>0)
            cur_accum|=(code<<cur_bits);
        else
            cur_accum=code;
        cur_bits+=n_bits;
        while (cur_bits>=8) {
            char_out((Byte)(cur_accum&0x00ff),outs);
            cur_accum>>=8;
            cur_bits-=8;
        }
        // If the next entry is going to be too big for the code size,
        // then increase it, if possible.
        if (free_ent>maxcode||clear_flg) {
            if (clear_flg) {
                maxcode=MAXCODE(n_bits=g_init_bits);
                clear_flg=false;
            }
            else {
                ++n_bits;
                if (n_bits==maxbits)
                    maxcode=maxmaxcode;
                else
                    maxcode=MAXCODE(n_bits);
            }
        }
        if (code==EOFCode) {
            // At EOF, write the rest of the buffer.
            while (cur_bits>0) {
                char_out((Byte)(cur_accum&0x00ff),outs);
                cur_accum>>=8;
                cur_bits-=8;
            }
            flush_char(outs);
        }
    }
};
#ifndef EOF
const Integer LZWEncoder::EOF=-1; /*= -1*/
#endif

const std::array<Integer,17> LZWEncoder::masks=
{
    0x00000000,
    0x00000001,
    0x00000003,
    0x00000007,
    0x0000000F,
    0x0000001F,
    0x0000003F,
    0x0000007F,
    0x000000FF,
    0x000001FF,
    0x000003FF,
    0x000007FF,
    0x00000FFF,
    0x00001FFF,
    0x00003FFF,
    0x00007FFF,
    0x0000FFFF
};
}

namespace mgui {
class QAnimatedGifEncoder::ThisData {
public:
    ThisData() {
        for (auto & ii:usedEntry) { ii=false; }
    }
    ~ThisData() {}

    Integer width=null; // image size
    Integer height=null;
    Color transparent=null; // transparent color if given
    Boolean isGivenTransparent=false;
    Integer transIndex=null; // transparent index in color table
    Integer repeat=-1; // no repeat
    Integer delay=0; // frame delay (hundredths)
    Boolean started=false; // ready to output frames
    OutputStream * out=0;
    BufferedImage image; // current frame
    PixType  pixels; // BGR byte array from frame
    QVector<Byte> indexedPixels; // converted frame indexed to palette
    Integer colorDepth=8; // number of bit planes
    QVector<Byte> colorTab; // RGB palette
    Boolean usedEntry[256]; // active palette entries
    Integer palSize=7; // color table size (bits-1)
    Integer dispose=-1; // disposal code (-1 = use default)
    Boolean closeStream=false; // close stream when finished
    Boolean firstFrame=true;
    Boolean sizeSet=false; // if false, get size from first frame
    Integer sample=10; // default sample interval for quantizer
};

QAnimatedGifEncoder::QAnimatedGifEncoder() {
    ThisData * var_thisData=new ThisData;
    thisData={
            var_thisData,
            [](ThisData * par_data) {delete par_data; }
    };
}


QAnimatedGifEncoder::~QAnimatedGifEncoder() {
    if (this->thisData->started)
        this->finish();
}

void QAnimatedGifEncoder::setDelay(const Integer ms) {
    ThisData * var_thisData=thisData.get();
    var_thisData->delay=std::round(ms/10.0f);
}

void QAnimatedGifEncoder::setDispose(const Integer code) {
    if (code>=0) {
        ThisData * var_thisData=thisData.get();
        var_thisData->dispose=code;
    }
}

void QAnimatedGifEncoder::setRepeat(const Integer iter) {
    if (iter>=0) {
        ThisData * var_thisData=thisData.get();
        var_thisData->repeat=iter;
    }
}

void QAnimatedGifEncoder::setTransparent(const Color c) {
    ThisData * var_thisData=thisData.get();
    var_thisData->isGivenTransparent=true;
    var_thisData->transparent=c;
}

void QAnimatedGifEncoder::setSize(const Integer w,const Integer h) {
    ThisData * var_thisData=thisData.get();
    if ((var_thisData->started)&&(!(var_thisData->firstFrame))) return;

    var_thisData->width=w;
    var_thisData->height=h;

    if (var_thisData->width<1) var_thisData->width=320;
    if (var_thisData->height<1) var_thisData->height=240;

    var_thisData->sizeSet=true;
}

void QAnimatedGifEncoder::getImagePixels() {
    ThisData * var_thisData=thisData.get();
    auto w=var_thisData->image.width();
    auto h=var_thisData->image.height();
    QImage::Format type=var_thisData->image.format();
    if ((w!=var_thisData->width)
            ||(h!=var_thisData->height)
            ||(type!=QImage::Format::Format_RGB888)) {
        // create new image with right size/format
        BufferedImage temp=BufferedImage(
            var_thisData->width,
            var_thisData->height,
            QImage::Format::Format_RGB888);
        QPainter var_painter(&temp);
        var_painter.drawImage(0,0,var_thisData->image);
        var_thisData->image=std::move(temp);
    }
    {//set bits
        const auto var_w=var_thisData->image.width();
        const auto var_h=var_thisData->image.height();
        QImage & im=var_thisData->image;
        auto & pixs=var_thisData->pixels;
        pixs.clear();
        pixs.reserve(im.byteCount());
        for (auto ii=0; ii<var_h; ++ii) {//qimage这里必须拷贝 因为内存对其  W = ( w * bitcount + 31 )/32 * 4;
            for (auto jj=0; jj<var_w; ++jj) {
                auto var_pix=var_thisData->image.pixel(jj,ii);
                pixs.push_back(Byte(qRed(var_pix)));
                pixs.push_back(Byte(qGreen(var_pix)));
                pixs.push_back(Byte(qBlue(var_pix)));
            }
        }
    }
    //
}


Boolean QAnimatedGifEncoder::addFrame(BufferedImage && im) {
    ThisData * var_thisData=thisData.get();
    if ((im.width()<=null)||!var_thisData->started) {
        return false;
    }
    Boolean ok=true;

    if (false==var_thisData->sizeSet) {
        // use first frame's size
        setSize(im.width(),im.height());
    }

    var_thisData->image=im;
    var_thisData->image=var_thisData->image.scaled(
        QSize(var_thisData->width,var_thisData->height),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
    );

    getImagePixels(); // convert to correct format if necessary
    analyzePixels(); // build color table & map pixels

    if (var_thisData->firstFrame) {
        writeLSD(); // logical screen descriptior 逻辑屏幕标识符
        writePalette(); // global color table
        if (var_thisData->repeat>=0) {
            // use NS app extension to indicate reps
            writeNetscapeExt();
        }
    }

    writeGraphicCtrlExt(); // write graphic control extension
    writeImageDesc(); // image descriptor
    if (!(var_thisData->firstFrame)) {
        writePalette(); // local color table
    }
    writePixels(); // encode and write pixel data
    var_thisData->firstFrame=false;

    return ok;
}

void QAnimatedGifEncoder::writePalette() {
    ThisData * var_thisData=thisData.get();
    var_thisData->out->write(var_thisData->colorTab.data(),var_thisData->colorTab.size());
    Integer n=(3*256)-var_thisData->colorTab.size();
    for (Integer i=0; i<n; ++i) {
        writeSome(Byte(0),var_thisData->out);
    }
}

void QAnimatedGifEncoder::writePixels() {
    ThisData * var_thisData=thisData.get();
    LZWEncoder * encoder=
        new LZWEncoder(
            var_thisData->width,
            var_thisData->height,
            var_thisData->indexedPixels,
            var_thisData->colorDepth
        );
    std::unique_ptr<LZWEncoder> _(encoder);
    encoder->encode(var_thisData->out);
}

void QAnimatedGifEncoder::writeGraphicCtrlExt() {
    ThisData * var_thisData=thisData.get();
    var_thisData->out->put(0x21); // extension introducer
    var_thisData->out->put(Byte(0xf9)); // GCE label
    var_thisData->out->put(4); // data block size
    Integer transp,disp;
    if (var_thisData->isGivenTransparent==false) {
        transp=0;
        disp=0; // dispose = no action
    }
    else {
        transp=1;
        disp=2; // force clear if using transparent color
    }
    if (var_thisData->dispose>=0) {
        disp=var_thisData->dispose&7; // user override
    }
    disp<<=2;
    // packed fields
    var_thisData->out->put(Byte((disp|transp)&0x00ff)); // 8   transparency flag
    writeShort(var_thisData->delay); // delay x 1/100 sec
    var_thisData->out->put(Byte(0x00ff&var_thisData->transIndex)); // transparent color index
    var_thisData->out->put(0); // block terminator
}

void QAnimatedGifEncoder::writeLSD() {
    ThisData * var_thisData=thisData.get();
    // logical screen size
    writeShort(var_thisData->width);
    writeShort(var_thisData->height);
    // packed fields
    writeSome(Byte(0x80|0x70|0x00|var_thisData->palSize),var_thisData->out);
    writeSome(Byte(0),var_thisData->out);
    writeSome(Byte(0),var_thisData->out);
}

void QAnimatedGifEncoder::writeImageDesc() {
    ThisData * var_thisData=thisData.get();
    var_thisData->out->put(0x2c);
    writeShort(0); // image position x,y = 0,0
    writeShort(0);
    writeShort(var_thisData->width); // image size
    writeShort(var_thisData->height);
    // packed fields
    if (var_thisData->firstFrame) {
        // no LCT  - GCT is used for first (or only) frame
        var_thisData->out->put(0);
    }
    else {
        // specify normal LCT
        var_thisData->out->put(0x80|var_thisData->palSize); // 6-8 size of color table
    }
}

void QAnimatedGifEncoder::writeShort(Integer value) {
    ThisData * var_thisData=thisData.get();
    var_thisData->out->put(Byte(value&0x00ff));
    var_thisData->out->put(Byte((value>>8)&0x00ff));
}

void QAnimatedGifEncoder::writeNetscapeExt() {
    ThisData * var_thisData=thisData.get();
    var_thisData->out->put(0x21); // extension introducer
    writeSome(Byte(0xff),var_thisData->out); // app extension label
    var_thisData->out->put(11); // block size
    writeString((const Byte *)("NETSCAPE2.0")); // app id + auth code
    var_thisData->out->put(3); // sub-block size
    var_thisData->out->put(1); // loop sub-block id
    writeShort(var_thisData->repeat); // loop count (extra iterations, 0=repeat forever)
    var_thisData->out->put(0); // block terminator
}

Boolean QAnimatedGifEncoder::addFrame(const BufferedImage & im) {
    BufferedImage var_image=im;
    return addFrame(std::move(var_image));
}

static inline const Byte * gifTrailer() {//1
    static const Byte data[]={ 0x3b, 0 };
    return data;
}

static inline const Byte * gifHeader() {//6
    static const Byte data[]={ 'G', 'I', 'F', '8', '9', 'a', 0 };
    return data;
}

Boolean QAnimatedGifEncoder::finish() {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->started==false) return false;
    Boolean ok=true;
    var_thisData->started=false;
    //
    if (var_thisData->out==0) { ok=false; }
    else
        try {
        var_thisData->out->put(0x3b);
        var_thisData->out->flush();
        if (var_thisData->closeStream) {
            var_thisData->out->close();
        }
    }
    catch (...) {
        ok=false;
    }

    // reset for subsequent use
    var_thisData->transIndex=0;
    var_thisData->out=null;
    var_thisData->image=QImage();
    var_thisData->pixels.clear();
    var_thisData->indexedPixels.clear();
    var_thisData->colorTab.clear();
    var_thisData->closeStream=false;
    var_thisData->firstFrame=true;
    var_thisData->isGivenTransparent=false;

    return ok;
}

void QAnimatedGifEncoder::setFrameRate(const Float fps) {
    if (fps!=0.0f) {
        ThisData * var_thisData=thisData.get();
        var_thisData->delay=std::round(100.0f/fps);
    }
}

void QAnimatedGifEncoder::setQuality(const Integer quality) {
    ThisData * var_thisData=thisData.get();
    if (quality<1) {
        var_thisData->sample=1;
        return;
    }
    var_thisData->sample=quality;
}

/* 'G', 'I', 'F', '8', '9', 'a' */
Boolean QAnimatedGifEncoder::start(OutputStream & os) {
    ThisData * var_thisData=thisData.get();
    Boolean ok=true;
    var_thisData->closeStream=false;
    var_thisData->out=&os;

    try {
        writeString(gifHeader()); // header
    }
    catch (...) {
        ok=false;
    }
    var_thisData->started=ok;
    return ok;
}

Integer QAnimatedGifEncoder::findClosest(Color c) {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->colorTab.size()==null) return -1;
    Integer r=qRed(c);
    Integer g=qGreen(c);
    Integer b=qBlue(c);
    Integer minpos=0;
    Integer dmin=256*256*256;
    Integer len=Integer(var_thisData->colorTab.size());
    for (Integer i=0; i<len;) {
        Integer dr=r-(var_thisData->colorTab[i++]&0xff);
        Integer dg=g-(var_thisData->colorTab[i++]&0xff);
        Integer db=b-(var_thisData->colorTab[i]&0xff);
        Integer d=dr * dr+dg * dg+db * db;
        Integer index=i/3;
        if (var_thisData->usedEntry[index]&&(d<dmin)) {
            dmin=d;
            minpos=index;
        }
        ++i;
    }
    return minpos;
}


void QAnimatedGifEncoder::analyzePixels() {
    ThisData * var_thisData=thisData.get();
    typedef Integer size_type;
    auto len=size_type(var_thisData->pixels.size());
    auto nPix=len/size_type(3);
    var_thisData->indexedPixels.resize(nPix);
    QuantizationAlgorithm * nq=new NeuQuant;
    std::unique_ptr<QuantizationAlgorithm> uptr_nq(nq);
    nq->construct(var_thisData->pixels,len,var_thisData->sample);
    var_thisData->colorTab=nq->process();

    // map image pixels to new palette
    Integer k=0;
    for (Integer i=0; i<nPix; ++i) {
        //java规定求值顺序从左至右 但是C/C++无此规定
        const Integer k0=k++;
        const Integer k1=k++;
        const Integer k2=k++;

        Integer index=
            nq->map(
                Integer(var_thisData->pixels[k0])&0x000000ff,
                Integer(var_thisData->pixels[k1])&0x000000ff,
                Integer(var_thisData->pixels[k2])&0x000000ff
            );
        var_thisData->usedEntry[index]=true;
        var_thisData->indexedPixels[i]=(Byte)(index&0x000000ff);
    }
    var_thisData->pixels.clear();
    var_thisData->colorDepth=8;
    var_thisData->palSize=7;
    // get closest match to transparent color if specified
    if (var_thisData->isGivenTransparent) {//----
        var_thisData->transIndex=findClosest(var_thisData->transparent);
    }
}

void QAnimatedGifEncoder::writeString(const String & s) {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->out&&s.size()) {
        var_thisData->out->write(s.c_str(),s.size());
    }
}
}

