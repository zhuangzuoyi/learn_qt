#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QChart"

using namespace QtCharts;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
};

#endif // DIALOG_H
