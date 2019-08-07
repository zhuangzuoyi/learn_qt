#include "dialog.h"
#include "QVBoxLayout"
#include "QChart"
#include "QChartView"
#include "QSplineSeries"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setMinimumSize(500,500);
    QVBoxLayout *container;

    QChart *chart;
    QChartView *ChartView;
    QSplineSeries *series;

    series = new QSplineSeries(this);
    chart = new QChart();

    series->append(0,1);
    series->append(1,2);
    series->append(2,3);
    series->append(3,4);
    series->append(4,5);

    chart->addSeries(series);
    chart->createDefaultAxes();
    ChartView = new QChartView(this);
    ChartView->setChart(chart);

    container = new QVBoxLayout();
    container->addWidget(ChartView);

    this->setLayout(container);
}

Dialog::~Dialog()
{

}
