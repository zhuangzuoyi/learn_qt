#include "dialog.h"
#include "ui_dialog.h"
#include "QFile"
#include "QDebug"
#include "QTimer"
#include "QValueAxis"

#define SENSOR_PATH  "/sys/class/hwmon/hwmon0/temp1_input"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    f.setFileName(SENSOR_PATH);
//    if(!f.open(QIODevice::ReadOnly))
//    {
//        qDebug()<<"Open faile";
//        f.close();
//        return;
//    }

//    get_temp();

//    QList<double> cpu_temp;
//    QChart *temp_chart;
//    QChartView temp_view;
//    QSplineSeries   temp_line;
    cpu_temp.clear();
    temp_line = new QSplineSeries();
    temp_chart = new QChart();
    temp_chart->addSeries(temp_line);
//    temp_chart->axisX()->setRange(0,100);
//    temp_chart->axisY()->setRange(0,50);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%g");
    //axisX->setTitleText("Samples");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 50);
   // axisY->setTitleText("Audio level");
    temp_chart->setAxisX(axisX, temp_line);
    temp_chart->setAxisY(axisY, temp_line);
    temp_view = new QChartView(temp_chart);

//    ui->container->setContentsMargins(0,0,0,0);
//    ui->container->addWidget(temp_view);

//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(get_temp()));
//    timer->start(1000);
}

Dialog::~Dialog()
{
//    f.close();
    delete ui;
}


void Dialog::get_temp(void)
{
    if(f.isOpen())
        f.seek(0);
    else {
        if(!f.open(QIODevice::ReadOnly))
        {
            //this->ui->value->setText("Open faile");
            return;
        }
    }
    QString va = f.readAll();
    QString temp = va.left(2) + "." + va.mid(2,2) + "℃";
  //  this->ui->value->setText(temp);
}
