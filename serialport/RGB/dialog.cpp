#include "dialog.h"
#include "ui_dialog.h"
#include "QSerialPort"
#include "QDebug"
#include "QSerialPortInfo"
#include "QColorDialog"
#include "QColor"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        //QString menu_temp = info.portName() + ":" + info.description();
        ui->port_list->addItem(info.portName() );
    }

    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);


    serial.setBaudRate(115200);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_open_clicked()
{
    serial.close();
    serial.setPortName(ui->port_list->currentText());
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug()<<"Open "<<ui->port_list->currentText()<<" faile";
        return;
    }
    qDebug()<<ui->port_list->currentText();
}

void Dialog::on_send_clicked()
{
     QByteArray cmd;
     cmd.resize(8);
     cmd[0] = 0xaa;
     cmd[1] = 0x55;
     cmd[2] = 0x00;
     cmd[3] = 0x10;

     cmd[7] = 0x33;
     cmd[8] = 0xee;

     QColor color = QColorDialog::getColor(Qt::white, this);
     qDebug()<<"red:"<<color.red();
     qDebug()<<"greed"<<color.green();
     qDebug()<<"blue"<<color.blue();
     cmd[4] = color.red();
     cmd[5] = color.green();
     cmd[6] = color.blue();
     if(serial.isOpen())
     {
         serial.write(cmd);
     }
}
