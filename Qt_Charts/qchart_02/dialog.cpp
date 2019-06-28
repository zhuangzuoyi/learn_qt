#include "dialog.h"
#include "ui_dialog.h"
#include "QLineSeries"
#include "QDateTime"
#include "QDebug"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    series = new QSplineSeries(this);
    chart = new QChart();

    axisX = new QValueAxis();
    axisY = new QValueAxis();

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    chart->addSeries(series);
    axisX->setTickCount(5);
    axisX->setRange(0, 10);
    axisY->setRange(0, 10);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    ChartView = new QChartView(this);
    ChartView->setChart(chart);
    ui->verticalLayout->addWidget(ChartView);

    x_index = 0;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Timeout_handler()));
    timer->start(200);
}

Dialog::~Dialog()
{
    delete ui;
}




void Dialog::Timeout_handler()
{
    QDateTime dt;
    QString current_dt = dt.currentDateTime().toString("yyyy:MM:dd:hh:mm:ss:zzz");
    qsrand(dt.currentDateTime().toTime_t());
    int y = qrand() % 10;
    series->append(x_index,y);

    if(x_index > 10)
        axisX->setRange(x_index-10, x_index);
    x_index ++;
}
