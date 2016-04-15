#ifndef OPENCVUTILITY_0x00_HPP
#define OPENCVUTILITY_0x00_HPP() 1

#if !defined(MACRO_PROTECTED)
#define MACRO_PROTECTED protected
#endif

#include <opencv2/opencv.hpp>
#include "core_utility.hpp"
#include "quazip/quazip.h"
#include "quazip/quazipdir.h"
#include "quazip/quazipfile.h"
#include "quazip/quazipfileinfo.h"
#include "quazip/GZipCompressor.hpp"
#include "lua/lua.hpp"
#include <QtCore/qdir.h>
#include <QtCore/qobject.h>
#include <QtCore/qcommandlineoption.h>
#include <QtCore/qcommandlineparser.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qpainter.h>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>

class CORE_UTILITYSHARED_EXPORT OpenCVUtility :
    public QObject {
    Q_OBJECT
private:
    typedef QObject P;
protected:
    explicit OpenCVUtility(QObject *);
    virtual ~OpenCVUtility();
public:
    static void construct();
    typedef void(*Handle)(QVariant *);
    typedef void(*HandleQImage)(void *);
    static Handle getHandle();
    static HandleQImage getHandleQImage();
    static cv::Mat read(const QString &);
    static cv::Mat read(const QImage &);
    static QImage read(const cv::Mat &);
    static cv::Mat tryRead(const QImage &);
    static QImage tryRead(const cv::Mat &);
    static QImage getInnerQImage(const cv::Mat &);
    static cv::Mat getInnerOpenCVMat(const QImage &);
    static cv::Mat read(QImage &&);
    static QImage read(cv::Mat &&);
    static cv::Mat tryRead(QImage &&);
    static QImage tryRead(cv::Mat &&);
    static QImage getInnerQImage(cv::Mat &&);
    static cv::Mat getInnerOpenCVMat(QImage &&);
    static cv::MatAllocator * getReaderAllocator();
};

#include "OpenCVScene.hpp"
#include "OpenCVItem.hpp"
#include "OpenCVWindow.hpp"
#include "OpenCvStyle.hpp"
#include "OpenCVHistItem.hpp"
#include "OpenCVScatterItem.hpp"
#include "OpenCVLineSeriesItem.hpp"
#include "OpenCVChartImage.hpp"
#include "OpenCVVerticalItems.hpp"
#include "OpenCVException.hpp"
#include "OpenCVUserDataAllocator.hpp"

#endif // OPENCVUTILITY_HPP
