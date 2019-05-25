#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtBluetooth"
#include "QList"

#include "QChart"
#include "QChartView"
#include "QList"
#include "QSplineSeries"
#include <QtCharts/QChartGlobal>


QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


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
    void chart_init(void);
    void update_chart(double temperature);


    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QLowEnergyController *m_control;
    QList<QBluetoothDeviceInfo> m_devices;
    bool is_bt05_serve_found;
    QLowEnergyDescriptor m_notificationDesc;
    QLowEnergyService *m_service;

    QChart *chart;
    QChartView *ChartView;
    QList<double> temp_list;
    QSplineSeries *series;
    uint16_t index;
    double y_max;
};

#endif // MAINWINDOW_H
