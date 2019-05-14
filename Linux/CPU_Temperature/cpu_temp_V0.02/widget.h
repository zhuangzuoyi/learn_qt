#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QChart"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include "QSerialPort"

QT_CHARTS_USE_NAMESPACE



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    static const uint8_t line_max = 10;
private slots:
    void on_OpenCom_clicked();
    void serial_read_dat(void);
    void on_line_count_currentIndexChanged(int index);

private:
    void update_com(void);
    void line_data_update(QStringList current_data);
    Ui::Widget *ui;
    QChart *chart;
    QChartView *ChartView;
    QList<double> right,left,mid,real_data[10];
    QSerialPort serial;
    QSplineSeries *series;
    QSplineSeries series_buf[10];
    uint16_t index;
    double y_max;

    int current_line;
};

#endif // WIDGET_H
