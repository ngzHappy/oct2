/*run.cpp*/
#include <OpenCVUtility.hpp>
#include <opencv_application_configuration_file.hpp>
#include <QtCore/qdebug.h>
#include "private/opencv_fitEllipse_run_exception.cpp"
#include <QtCharts>

namespace {

QList<QPointF> genEllipse(const cv::RotatedRect & argRect) {
    enum  {SIZE=100};
    typedef double eval_type;
    auto varSize= argRect.size;
    if (varSize.width<=0) { return{}; }
    if (varSize.height<=0) { return{}; }
    QList<QPointF> varAns;
    varAns.reserve(SIZE);
    const eval_type varA=varSize.width/2;
    const eval_type varB=varSize.height/2;
    constexpr const eval_type varStep=3.141592654*2/SIZE;
    double varAngle=0;
    for (std::int_fast32_t i=0; i<SIZE;++i) {
        varAns.push_back({
            varA*std::cos(varAngle),
            varB*std::sin(varAngle) });
        varAngle+=varStep;
    }
    varAngle=argRect.angle/180*3.141592654;
    const eval_type a00=std::cos(varAngle);
    const eval_type a10=std::sin(varAngle);
    const eval_type a01=-a10;
    const eval_type a11=a00;
    const auto &varCenter=argRect.center;
    for (auto & i:varAns) {
        const eval_type varX=i.x()*a00+i.y()*a01+varCenter.x;
        const eval_type varY=i.x()*a10+i.y()*a11+varCenter.y;
        i.setX(varX); i.setY(varY);
    }
    return std::move(varAns);
}

}

namespace opencv_fitEllipse{
extern void run(OpenCVWindow * window) try{

    std::vector<cv::Point2f> varPointsInput;

    varPointsInput=
        CoreUtility::getConfigurationFile()
        .getInputData2D<float,std::vector< cv::Point2f >/**/>();

    auto varEllipse = cv::fitEllipse(varPointsInput);

    auto varItem = window->insertScatter(
        varPointsInput.begin(),
        varPointsInput.end()
        );

    auto varChart=varItem->getChart();
    QtCharts::QSplineSeries * varLine;
    {
        auto tvarLine=
            std::make_unique<std::remove_reference_t<decltype(*varLine)>>();
        auto varData=genEllipse(varEllipse);
        if (varData.isEmpty()) { return; }
        tvarLine->append(varData);
        tvarLine->append(varData.first().x(),varData.first().y());
        varLine=tvarLine.release();
        varChart->addSeries(varLine);
    }

    varChart->setAxisY(varChart->axisY(varItem->getScatterSeries()),varLine);
    varChart->setAxisX(varChart->axisX(varItem->getScatterSeries()),varLine);

    varItem->setWindowTitle(u8"椭圆拟合"_qs);
    varItem->resize(768-30,512-30);
    varLine->setPen(QPen(QColor(1,1,1),2));
}
catch (const cv::Exception &e) {
    opencv_exception::error(e,"get opencv exception",opencv_line(),opencv_file(),opencv_func());
}

}
