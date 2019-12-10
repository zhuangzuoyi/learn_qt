#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QSerialPort"

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
    void on_open_clicked();

    void on_send_clicked();

private:
    Ui::Dialog *ui;

    QSerialPort serial;
};

#endif // DIALOG_H
