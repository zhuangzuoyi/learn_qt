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

private:
    Ui::MainWindow *ui;
    void connect2device(void);
    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QLowEnergyController *m_control;
    QList<QBluetoothDeviceInfo> m_devices;
};

#endif // MAINWINDOW_H
