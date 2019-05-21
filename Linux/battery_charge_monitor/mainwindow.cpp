#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtBluetooth/QBluetoothDeviceDiscoveryAgent"
#include "QDebug"
#include "QtBluetooth"


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
    if (gatt == QBluetoothUuid(QBluetoothUuid::HeartRate)) {
    }
}


void MainWindow::serviceScanDone()
{
    qDebug()<<"Scan done";
}
