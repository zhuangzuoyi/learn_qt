#include "showdialog.h"
#include "ui_showdialog.h"

showdialog::showdialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showdialog)
{
    ui->setupUi(this);
}

showdialog::~showdialog()
{
    delete ui;
}
