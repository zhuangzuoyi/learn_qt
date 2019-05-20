#include "dialog.h"
#include "ui_dialog.h"
#include "QFile"
#include "QDebug"
#include "QTimer"
#include "QValueAxis"
#include "QDateTime"
#include "QList"


#define SENSOR_PATH  "/sys/class/hwmon/hwmon0/temp1_input"
#define x_count_max 100

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

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    y_max = 0xffff;
    chart->axisX()->setRange(0, x_count_max);
    chart->axisY()->setRange(20, 80);
    series = new QSplineSeries();
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    ChartView = new QChartView(chart);
    ChartView->setRenderHint(QPainter::Antialiasing);
    ui->container->addWidget(ChartView);

    log_file_name.clear();
    set_log_file_name();


    temp_list.clear();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(get_temp()));
    timer->start(1000);
}

Dialog::~Dialog()
{
    f.close();
    logfile.close();
    delete ui;
}


void Dialog::update_chart(double temperature)
{
    QList<QPointF> point_temp;
    point_temp.clear();
    temp_list.append(temperature);
    if(temp_list.length() > x_count_max)
    {
        temp_list.removeFirst();

        for(int i=0;i<x_count_max;i++)
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

    QDateTime dateTime;
    QString dateTime_str = dateTime.currentDateTime().toString("yyyy:MM:dd:hh:mm:ss");
    qDebug()<<dateTime_str;
    save_temperature(dateTime_str,temp);
}

void Dialog::set_log_file_name(void)
{
    QDateTime dateTime;
    QString dateTime_str = dateTime.currentDateTime().toString("yyyy:MM:dd:hh:mm:ss");
    QList<QString> timelist = dateTime_str.split(":");
    log_file_name = timelist.at(0)+timelist.at(1)+timelist.at(2)+timelist.at(3)+timelist.at(4);
    //QFile fFile(fpPath);
    logfile.setFileName(log_file_name);
    if(logfile.open(QIODevice::WriteOnly | QIODevice::Text))
        save_stream.setDevice(&logfile);
}


void Dialog::save_temperature(QString time,QString temper)
{
    if(!logfile.isOpen())
    {
        if(!logfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        save_stream.setDevice(&logfile);
    }
    save_stream<<time<<","<<temper<<endl;
}
