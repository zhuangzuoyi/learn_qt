#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtBluetooth/QBluetoothDeviceDiscoveryAgent"
#include "QDebug"
#include "QtBluetooth"
#include "QValueAxis"


#define x_count_max 100


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &MainWindow::addDevice);
    connect(m_deviceDiscoveryAgent, static_cast<void (QBluetoothDeviceDiscoveryAgent::*)(QBluetoothDeviceDiscoveryAgent::Error)>(&QBluetoothDeviceDiscoveryAgent::error),
          this, &MainWindow::deviceScanError);

    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, &MainWindow::deviceScanFinished);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled, this, &MainWindow::deviceScanFinished);
    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);

    is_bt05_serve_found = false;

    chart_init();
}


void MainWindow::chart_init(void)
{
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("Battery'Voltage");

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    y_max = 0xffff;
    chart->axisX()->setRange(0, x_count_max);
    chart->axisY()->setRange(3.0, 5.0);
    series = new QSplineSeries();
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    ChartView = new QChartView(chart);
    ChartView->setRenderHint(QPainter::Antialiasing);
    ui->container->addWidget(ChartView);

    temp_list.clear();
}

void MainWindow::update_chart(double temperature)
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



void MainWindow::addDevice(const QBluetoothDeviceInfo &device)
{
    // If device is LowEnergy-device, add it to the list
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        m_devices.append(device);
        qDebug()<<device.name()<<","<<device.address();
        ui->device_list->addItem(device.name());
    }
    //...
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_to_device_clicked()
{
        connect2device();
}

void MainWindow::on_scan_device_clicked()
{
    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}



void MainWindow::deviceScanFinished()
{
    qDebug()<<"scan finish";
}


void MainWindow::deviceScanError(QBluetoothDeviceDiscoveryAgent::Error error)
{

}


void MainWindow::connect2device(void)
{
    QBluetoothDeviceInfo m_currentDevice = m_devices.at(ui->device_list->currentIndex());
    qDebug()<<"Connect to:"<<m_currentDevice.name();
    m_control = QLowEnergyController::createCentral(m_currentDevice, this);
    connect(m_control, &QLowEnergyController::serviceDiscovered,this, &MainWindow::serviceDiscovered);
    connect(m_control, &QLowEnergyController::discoveryFinished,this, &MainWindow::serviceScanDone);

    connect(m_control, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
            this, [this](QLowEnergyController::Error error) {
        Q_UNUSED(error);
    });
    connect(m_control, &QLowEnergyController::connected, this, [this]() {
        m_control->discoverServices();
    });
    connect(m_control, &QLowEnergyController::disconnected, this, [this]() {
    });
    // Connect
    m_control->connectToDevice();
}


void MainWindow::serviceDiscovered(const QBluetoothUuid &gatt)
{
    qDebug()<<"Discovered GATT:"<<gatt.toString();
    QString battery_serer("0000ffe0-0000-1000-8000-00805f9b34fb");
    QBluetoothUuid bt05(battery_serer);// = new QBluetoothUuid("0000ffe0-0000-1000-8000-00805f9b34fb");
    if (gatt == QBluetoothUuid(QBluetoothUuid::HeartRate)) {
    }
    if(gatt == bt05)
    {
        qDebug()<<"Found server";
        is_bt05_serve_found = true;
    }
}


void MainWindow::serviceScanDone()
{
    qDebug()<<"Scan done";

    if (is_bt05_serve_found)
        m_service = m_control->createServiceObject(QBluetoothUuid(QString("0000ffe0-0000-1000-8000-00805f9b34fb")), this);

    if (m_service) {
        connect(m_service, &QLowEnergyService::stateChanged, this, &MainWindow::serviceStateChanged);
        connect(m_service, &QLowEnergyService::characteristicChanged, this, &MainWindow::updateHeartRateValue);
        connect(m_service, &QLowEnergyService::descriptorWritten, this, &MainWindow::confirmedDescriptorWrite);
        m_service->discoverDetails();
    } else {

    }

}


void MainWindow::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    switch (s) {
    case QLowEnergyService::DiscoveringServices:
            qDebug()<<"Discovering services...";
        break;
    case QLowEnergyService::ServiceDiscovered:
    {
        qDebug()<<"Service discovered.";
        const QLowEnergyCharacteristic hrChar = m_service->characteristic(QBluetoothUuid(QString("0000ffe1-0000-1000-8000-00805f9b34fb")));
        if (!hrChar.isValid()) {
                qDebug()<<"HR Data not found.";
            break;
        }

        m_notificationDesc = hrChar.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
        if (m_notificationDesc.isValid())
            m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));

        break;
    }
    default:
        //nothing for now
        break;
    }

}


void MainWindow::updateHeartRateValue(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    // ignore any other characteristic change -> shouldn't really happen though
    if (c.uuid() != QBluetoothUuid(QString("0000ffe1-0000-1000-8000-00805f9b34fb")))
        return;
    qDebug()<<value;
    if(value.startsWith("S") && value.endsWith("E"))
    {
        QList<QString> temp_list = QString(value).split(":");
        qDebug()<<temp_list;
        QString voltage_str;
        voltage_str.append(temp_list.at(2).at(0)).append(".").append(temp_list.at(2).at(1));
        update_chart(voltage_str.toDouble());
    }


}


void MainWindow::confirmedDescriptorWrite(const QLowEnergyDescriptor &d, const QByteArray &value)
{

}
