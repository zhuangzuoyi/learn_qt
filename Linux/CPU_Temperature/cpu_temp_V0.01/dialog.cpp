#include "dialog.h"
#include "ui_dialog.h"
#include "QFile"
#include "QDebug"
#include "QTimer"

#define SENSOR_PATH  "/sys/class/hwmon/hwmon0/temp1_input"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    get_temp();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(get_temp()));
    timer->start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::get_temp(void)
{
    QFile f(SENSOR_PATH);
    if(!f.open(QIODevice::ReadOnly))
    {
        this->ui->value->setText("Open faile");
        return;
    }
    QString va = f.readAll();
    QString temp = va.left(2) + "." + va.mid(2,2) + "℃";
    this->ui->value->setText(temp);
    f.close();
}
