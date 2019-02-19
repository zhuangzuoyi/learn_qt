#include "widget.h"
#include "ui_widget.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QDataStream"
#include "QDebug"
#include "showdialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->ui->file_path->setReadOnly(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("Binary Files(*.rgb *.argb *.data)"));
    this->ui->file_path->setText(path);
}

void Widget::on_ok_clicked()
{
//    showdialog *dlg = new showdialog(this);
//    dlg->show();

    QString file_name = this->ui->file_path->text();
    if(file_name.length() ==0)
    {
        QMessageBox::information(NULL, "ERROR", "No select file", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QByteArray source_data = file.readAll();
    file.close();

    int pixel_size = this->ui->pixel_size->text().toInt();
    int img_data_size = this->ui->img_height->text().toInt() * this->ui->img_width->text().toInt() * pixel_size;

    if(source_data.length() != img_data_size)
    {
        qDebug()<<"size is error";
        QMessageBox::information(NULL, "ERROR", "Size no correct", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    this->ui->imgShow->setHeight(this->ui->img_height->text().toInt());
    this->ui->imgShow->setWidth(this->ui->img_width->text().toInt());
    this->ui->imgShow->setFilePath(file_name);
    this->ui->imgShow->setPixelSize(this->ui->pixel_size->text().toInt());
    this->ui->imgShow->setImgData(source_data);
    this->ui->imgShow->update();
}
