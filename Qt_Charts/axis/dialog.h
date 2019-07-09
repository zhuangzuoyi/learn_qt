#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCharts>


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

private:
    Ui::Dialog *ui;

    QChartView *ChartView;
    QChart *chart;
    QValueAxis *axisX;
    QValueAxis *axisY;
};

#endif // DIALOG_H
