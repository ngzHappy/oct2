#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtWidgets/qslider.h>

namespace first_window{
extern void run(OpenCVWindow * window) {

    /*测试图片显示*/
    {
        intptr_t count_=0;
        const auto images_names=
            CoreUtility::getConfigurationFile().getInputImagesNames("images:000001");

        for (const auto & image_name:images_names) {
            window->insertImage(QImage(image_name))
                ->setWindowTitle(u8"第%1幅图片"_qs.arg(++count_));
        }
    }
    /*测试柱状图*/
    window->insertHist({ 1,2,3,4,5 })->setWindowTitle(u8"柱状图"_qs);
    /*测试散点图*/
    auto scatter=window->insertScatter({ {0,0},{1,1},{2,2} });
    scatter->setCentrePointPaint(
        std::shared_ptr< std::function<void(QPainter *)> >(
        new std::function<void(QPainter *)>{
        [](QPainter * painter) {
        painter->setBrush(Qt::transparent);
        painter->setPen(QPen(QColor(0,0,0),1));
        painter->drawRect(QRect{-10,-10,20,20});
    }
    }
        )
        );
    scatter->setWindowTitle(u8"散点图"_qs);
    /*测试折线图*/
    auto line_serie=window->insertLineSeries({ {0,0},{1,1},{2,2},{2,0},{0,0} });
    line_serie->setWindowTitle(u8"折线图"_qs);

    {
        OpenCVVerticalItems * item=new OpenCVVerticalItems(line_serie);
        item->addWidget(new QSlider(Qt::Horizontal));
        item->addWidget(new QSlider(Qt::Horizontal));
        item->addWidget(new QSlider(Qt::Horizontal));
    }
}
}
