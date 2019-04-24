#include "widget.h"
#include "ui_widget.h"
#include "QImage"
#include "qDebug"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QImage img("logo.bmp");
    qDebug()<<img.height()<<img.width();
    QByteArray sending_data(552,0);
    unsigned char bitmask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
    for(int j=0;j<img.height();j++)
    {

        for(int i=0;i<img.width();i++)
        {
            // |
            // |
            // V
            int y_index = j % 8;
            //----->
            int x_index = j / 8 * img.width() + i;

            if(img.pixelColor(i,j).value()==0)
            {
                sending_data[x_index] = (sending_data[x_index] | bitmask[y_index]) & 0x000000ff;
            }
            else
            {
            }
        }
    }

    int img_row,img_list;
    int dat_num=0;
    img_list=img.width();
    if((img.height() %8)>0)
    {
        img_row = (img.height() /8 +1) ;
    }else
        img_row = (img.height() /8);
    dat_num = img_row * img_list;
    QString last;
    last.clear();
    for(int k=0;k<dat_num;k++)
    {
        char l = (sending_data[k] & 0x0000000f);
        if(l > 9)
            l =l + 'a'-10;
        else
            l = l + '0';
        char h = (sending_data[k] & 0x000000f0) >>4;

        if(h > 9)
            h =h + 'a'-10;
        else
            h = h + '0';
        QString le = "0x"+QString(h)+QString(l)+',';
        last.append(le);
    }
    qDebug()<<last;
}

Widget::~Widget()
{
    delete ui;
}
