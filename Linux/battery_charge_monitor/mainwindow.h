#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtBluetooth"
#include "QList"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connect_to_device_clicked();

    void on_scan_device_clicked();
    void addDevice(const QBluetoothDeviceInfo &device);
    void deviceScanFinished();
    void deviceScanError(QBluetoothDeviceDiscoveryAgent::Error);
    void serviceDiscovered(const QBluetoothUuid &gatt);
    void serviceScanDone();
    void serviceStateChanged(QLowEnergyService::ServiceState s);
    void updateHeartRateValue(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void confirmedDescriptorWrite(const QLowEnergyDescriptor &d, const QByteArray &value);
private:
    Ui::MainWindow *ui;
    void connect2device(void);
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QLowEnergyController *m_control;
    QList<QBluetoothDeviceInfo> m_devices;
    bool is_bt05_serve_found;
    QLowEnergyDescriptor m_notificationDesc;
    QLowEnergyService *m_service;
};

#endif // MAINWINDOW_H
