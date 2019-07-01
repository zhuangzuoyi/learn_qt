#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QChart>
#include <QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include "QTimer"
using namespace QtCharts;


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void Timeout_handler();



private:
    Ui::Dialog *ui;

    QSplineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QList<int> y_list;
    QChart *chart;
    QChartView *ChartView;

    uint16_t x_index;
};

#endif // DIALOG_H
