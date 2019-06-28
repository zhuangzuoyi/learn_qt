#include "dialog.h"
#include "ui_dialog.h"
#include "QLineSeries"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    chart = new QChart();

    QLineSeries* series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(4,8);
    series->append(8,10);
    series->append(10,12);



    chart->addSeries(series);
    chart->createDefaultAxes();

    ChartView = new QChartView(this);
    ChartView->setChart(chart);
    ui->verticalLayout->addWidget(ChartView);


}

Dialog::~Dialog()
{
    delete ui;
}




