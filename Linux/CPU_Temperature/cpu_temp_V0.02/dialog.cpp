#include "dialog.h"
#include "ui_dialog.h"
#include "QFile"
#include "QDebug"
#include "QTimer"
#include "QValueAxis"

#define SENSOR_PATH  "/sys/class/hwmon/hwmon1/temp1_input"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    f.setFileName(SENSOR_PATH);
    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Open faile";
        f.close();
        return;
    }



    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("CPU temperature");

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    axisX->setRange(0, 100);
    axisY->setRange(20, 80);
    series = new QSplineSeries();
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    ChartView = new QChartView(chart);
    ChartView->setRenderHint(QPainter::Antialiasing);
    ui->container->addWidget(ChartView);

    temp_list.clear();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(get_temp()));
    timer->start(1000);
}

Dialog::~Dialog()
{
    f.close();
    delete ui;
}


void Dialog::update_chart(double temperature)
{
    QList<QPointF> point_temp;
    point_temp.clear();
    temp_list.append(temperature);
    if(temp_list.length() > 100)
    {
        temp_list.removeFirst();

        for(int i=0;i<100;i++)
        {
            QPointF node(i,temp_list.at(i));
            point_temp.append(node);
        }
    }else {
        for(int i=0;i<temp_list.length();i++)
        {
            QPointF node(i,temp_list.at(i));
            point_temp.append(node);
        }
    }
    series->replace(point_temp);
}

void Dialog::get_temp(void)
{
    if(f.isOpen())
        f.seek(0);
    else {
        if(!f.open(QIODevice::ReadOnly))
        {
            return;
        }
    }
    QString va = f.readAll();
    QString temp = va.left(2) + "." + va.mid(2,2);
    qDebug()<<temp+ + "℃";
    update_chart(temp.toDouble());
}
