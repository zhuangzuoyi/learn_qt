#include <QCoreApplication>
#include "QtSerialPort/QSerialPortInfo"
#include <iostream>
#include "QtDebug"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QString menu_temp = info.portName() + " : " + info.description();
        qDebug() << menu_temp;
    }
}
