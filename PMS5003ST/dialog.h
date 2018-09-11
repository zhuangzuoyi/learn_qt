#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtNetwork>
#include <QChart>
#include <QChartView>
#include <QList>
#include <QSplineSeries>
#include <QScatterSeries>
using namespace QtCharts;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void tcp_send();
    void tcp_connect();
    void temp_update(uint16_t dat);
    void chart_init(void);
    void hum_update(uint16_t dat);
    void hcho_update(uint16_t dat);
    void pm1_update(uint16_t dat);
    void pm25_update(uint16_t dat);
    void pm10_update(uint16_t dat);
    void seve_data(QString filename,QString Dat);
    void Save_source_data(QString filename,QByteArray dat);
private:
    Ui::Dialog *ui;
    QTcpSocket *tcpSocket;
    int maxSize;  // data 最多存储 maxSize 个元素
    int maxX;
    int maxY;
    int max_dat_y;
    QList<double> data; // 存储业务数据的 list
    QChart *chart;
    QChartView *chartView;
    QSplineSeries *splineSeries;
    QScatterSeries *scatterSeries;
    //PM1.0
    int pm1_maxSize;  // data 最多存储 maxSize 个元素
    int pm1_maxX;
    int pm1_maxY;
    int pm1_max_dat_y;
    QList<double> pm1_data; // 存储业务数据的 list
    QChart *pm1_chart;
    QChartView *pm1_chartView;
    QSplineSeries *pm1_splineSeries;
    QScatterSeries *pm1_scatterSeries;
    //pm25
    int pm25_maxSize;  // data 最多存储 maxSize 个元素
    int pm25_maxX;
    int pm25_maxY;
    int pm25_max_dat_y;
    QList<double> pm25_data; // 存储业务数据的 list
    QChart *pm25_chart;
    QChartView *pm25_chartView;
    QSplineSeries *pm25_splineSeries;
    QScatterSeries *pm25_scatterSeries;
    //pm10
    int pm10_maxSize;  // data 最多存储 maxSize 个元素
    int pm10_maxX;
    int pm10_maxY;
    int pm10_max_dat_y;
    QList<double> pm10_data; // 存储业务数据的 list
    QChart *pm10_chart;
    QChartView *pm10_chartView;
    QSplineSeries *pm10_splineSeries;
    QScatterSeries *pm10_scatterSeries;
    //hcho
    int hcho_maxSize;  // data 最多存储 maxSize 个元素
    int hcho_maxX;
    int hcho_maxY;
    int hcho_max_dat_y;
    QList<double> hcho_data; // 存储业务数据的 list
    QChart *hcho_chart;
    QChartView *hcho_chartView;
    QSplineSeries *hcho_splineSeries;
    QScatterSeries *hcho_scatterSeries;
    //hum
    int hum_maxSize;  // data 最多存储 maxSize 个元素
    int hum_maxX;
    int hum_maxY;
    int hum_max_dat_y;
    QList<double> hum_data; // 存储业务数据的 list
    QChart *hum_chart;
    QChartView *hum_chartView;
    QSplineSeries *hum_splineSeries;
    QScatterSeries *hum_scatterSeries;

    uint16_t save_count;
    uint8_t source_flag;
private slots:
    void read_message();  //接收数据
    void on_tcp_send_clicked();
    void on_tcp_connect_clicked();
    void tcp_connected();
};

#endif // DIALOG_H
