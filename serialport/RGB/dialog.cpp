#include "dialog.h"
#include "ui_dialog.h"
#include "QSerialPort"
#include "QDebug"
#include "QSerialPortInfo"


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

}
