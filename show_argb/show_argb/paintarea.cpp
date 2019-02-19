#include "paintarea.h"
#include <QPainter>
#include <QDebug>

PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400,400);
    img_width =0;
    img_height =0;
    pixel_size =0 ;
    file_path = "";
}


void PaintArea::setWidth(int width)
{
    this->img_width = width;
}

void PaintArea::setHeight(int height)
{
    this->img_height = height;
}

void PaintArea::setPixelSize(int size)
{
    this->pixel_size = size;
}

void PaintArea::setFilePath(QString file)
{
    this->file_path = file;
}

void PaintArea::setImgData(QByteArray img_dat)
{
    img_data = img_dat;

    qDebug()<<img_data.at(10);
    int i= img_data[10] & 0x000000FF;

    qDebug("The first byte:%d",i);
    qDebug("The first byte:%d",img_data.at(10) & 0x000000FF);
    qDebug("The first byte:%x",img_data.at(10));

}


void PaintArea::paintEvent(QPaintEvent *)
{
    if(this->img_height == 0 || this->img_width ==0 || this->pixel_size==0 || this->file_path.isEmpty())
    {
        return;
    }
    QPainter painter(this);
    QPen pen(QColor(0,0,0));
    painter.setPen(pen);
//    p.setBrush(brush);

    qDebug()<<"size:"<<this->img_width<<","<<this->img_height;
    qDebug()<<"pixel:"<<this->pixel_size;
    qDebug()<<"Path:"<<this->file_path;
//    qDebug()<<img_data;
    int i=0,j=0;
    for( i=0;i<this->img_height;i++)
    {
        for(j=0;j<this->img_width;j++)
        {
            int r = img_data[(i*this->img_width+j)*4+1] & 0x000000FF;
            int g = img_data[(i*this->img_width+j)*4+2] & 0x000000FF;
            int b = img_data[(i*this->img_width+j)*4+3] & 0x000000FF;

            pen.setColor(QColor(r,g,b));
            qDebug()<<r<<g<<b;

            painter.setPen(pen);
            painter.drawPoint(j,i);
        }
    }

}
