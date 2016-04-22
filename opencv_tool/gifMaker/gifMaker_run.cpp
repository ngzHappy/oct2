/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/gifMaker_run_exception.cpp"
#include "QAnimatedGifEncoder.h"
#include <sstream>
#include <QtWidgets/qfiledialog.h>
//#include <QtCharts>

namespace gifMaker {
extern void run(OpenCVWindow * window) try {

    int count=0;
    const auto gifMakerData=
        CoreUtility::getConfigurationFile()
        .getInputGifMaderData();

    if (gifMakerData) {
        QString saveFileName=
            QFileDialog::getSaveFileName();
        if (saveFileName.isEmpty()) { return; }
        QFile file(saveFileName);
        if (file.open(QIODevice::WriteOnly)) {
            auto gifMaker=std::make_shared<mgui::QAnimatedGifEncoder>();
            gifMaker->setSize(gifMakerData.width,gifMakerData.height);
            gifMaker->setRepeat(0);
            gifMaker->start(file);
            for (const auto & i:*gifMakerData.data) {
                QImage inputImage(i.fileName);
                gifMaker->setDelay(i.time);
                gifMaker->addFrame(inputImage);
                window->insertImage(inputImage)
                    ->setWindowTitle(QString("%1").arg(count));
            }
            gifMaker->finish();
        }
    }

}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}/*~namespace*/

