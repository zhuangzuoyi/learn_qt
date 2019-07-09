#include "dialog.h"
#include "ui_dialog.h"
#include "QLineSeries"
#include "QValueAxis"
#include <QtCore/QDateTime>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    int daily_temp_max[30] = {32,
            31,30,30,31,32,32,32,
            32,32,32,31,31,31,31,
            30,30,31,32,32,33,33,
            30,30,30,30,31,31,31,
            33};

    QLineSeries* temp_max_series = new QLineSeries();
    QDateTime Time;
    for(int i=0;i<30;i++)
    {

         Time.setDate(QDate(2019, 6 , i));
        temp_max_series->append(Time.toMSecsSinceEpoch(),daily_temp_max[i]);
    }




    chart = new QChart();
    chart->addSeries(temp_max_series);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    QDateTime TimeMin;
    QDateTime TimeMax;
    TimeMin.setDate(QDate(2019, 6 , 1));
    TimeMax.setDate(QDate(2019, 6 , 30));
    axisX->setRange(TimeMin,TimeMax);
    axisX->setTickCount(10);
    axisX->setFormat("yy,MM,d");
    axisX->setTitleText("Date");

    chart->addAxis(axisX, Qt::AlignBottom);


    axisY = new QValueAxis();
    chart->addAxis(axisY,Qt::AlignLeft);
    axisY->setRange(29, 34);

    temp_max_series->attachAxis(axisX);
    temp_max_series->attachAxis(axisY);


    ChartView = new QChartView(this);
    ChartView->setChart(chart);
    ui->verticalLayout->addWidget(ChartView);
}

Dialog::~Dialog()
{
    delete ui;
}
