#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QFile"
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

class XYSeriesIODevice;




namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void get_temp(void);

private:
    void update_chart(double temperature);
    Ui::Dialog *ui;
    QFile f;

    QChart *chart;
    QChartView *ChartView;
    QList<double> temp_list;
    QSplineSeries *series;
    uint16_t index;
    double y_max;
};

#endif // DIALOG_H
