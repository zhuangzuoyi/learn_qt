#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QChart>
#include <QChartView>

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

    QChart *chart;
    QChartView *ChartView;
};

#endif // DIALOG_H
