#include "widget.h"
#include "ui_widget.h"
#include "QSerialPortInfo"
#include "QDebug"

#define Y_MARGIN 10
#define x_count_max 300
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    update_com();


    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("Multiaxis chart example");

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
//    axisX->setTickCount(20);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    y_max = 0xffff;
    chart->axisX()->setRange(0, 300);
    chart->axisY()->setRange(0, y_max);


    for(int i=0;i<line_max;i++)
    {
        chart->addSeries(&series_buf[i]);
        series_buf[i].attachAxis(axisX);
        series_buf[i].attachAxis(axisY);
    }


    ChartView = new QChartView(chart);
    ChartView->setRenderHint(QPainter::Antialiasing);
    ui->container->addWidget(ChartView);


    for(int i=0;i<line_max;i++)
    {
        real_data->clear();
    }
    connect(&serial, &QSerialPort::readyRead, this,&Widget::serial_read_dat);
    index =0;
    current_line = ui->line_count->currentIndex();
}


void Widget::update_com(void)
{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ui->com_port->addItem(info.portName());
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_OpenCom_clicked()
{
    serial.close();
    serial.setPortName(ui->com_port->currentText());
    serial.setBaudRate(ui->baudrate->currentText().toInt());
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug()<<"Open faile";
        return;
    }
}


void Widget::serial_read_dat(void)
{
    QString temp = serial.readLine();
    temp.remove(temp.length()-2,2);

    QStringList all =temp.split(",");

    if(all.length() >= current_line)
    {
        line_data_update(all);
    }
}

void Widget::line_data_update(QStringList current_data)
{
    QList<QPointF> point_temp;
    for(int i=0;i<current_data.length();i++)
    {
        double dat_temp = current_data.at(i).toDouble();
        if(dat_temp > y_max)
       {
            y_max = dat_temp;
            chart->axisY()->setRange(0, y_max + Y_MARGIN);
        }
        real_data[i].append(dat_temp);
    }

    if(real_data[0].length() > x_count_max)
    {
        for(int i=0;i<current_data.length();i++)
        {
            real_data[i].removeFirst();
            point_temp.clear();
            for(int j=0;j<x_count_max;j++)
            {
                QPointF t(j,real_data[i].at(j));
                point_temp.append(t);
            }
            series_buf[i].clear();
            series_buf[i].replace(point_temp);
        }
    }else {

        for(int i=0;i<current_data.length();i++)
        {
            point_temp.clear();

            for(int j=0;j<real_data[0].length();j++)
            {
                QPointF t(j,real_data[i].at(j));
                point_temp.append(t);
            }
            series_buf[i].clear();
            series_buf[i].replace(point_temp);
        }
    }

}


void Widget::on_line_count_currentIndexChanged(int index)
{
    current_line = index;
}
