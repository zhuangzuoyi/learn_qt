#include "widget.h"
#include "ui_widget.h"
#include "QStyle"
#include "QFileDialog"
#include "QMovie"
#include "QDebug"
#include "QUdpSocket"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 255, 255));
    ui->Showgif->setAutoFillBackground(true);
    ui->Showgif->setPalette(palette);
    ui->Showgif->setAlignment(Qt::AlignCenter);

    current_frame_index = 0;

    movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);
    connect(movie,SIGNAL(updated(QRect)),this,SLOT(framechange()));

    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::AnyIPv4,8266);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newClientConnect()));
    tcpSocket = NULL;
    is_img_load = false;
    img_row=0;
    img_list=0;
    process_step =0;
    ui->Showgif->setMovie(movie);

    load_gif();
}

void Widget::newClientConnect(void)
{
    log("new client connect");
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disConnect()));
    //init
    process_step =0;
    load_gif();
}

void Widget::readMessage()
{
    QByteArray buf;
    buf = tcpSocket->readAll();
    current_frame_index ++;
    movie->jumpToFrame(current_frame_index);
}

void Widget::disConnect()
{
    qDebug() << "client disconnect";
    process_step =0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::load_gif()
{
   QString fileName = ":image/Bad Apple.gif";
   if(fileName.isEmpty())
       return;
   movie->setFileName(fileName);
   is_img_load = true;
   process_step =0;
   movie->jumpToFrame(current_frame_index);

}

void Widget::send_process(QByteArray dat,int len)
{
    if(tcpSocket != NULL)
    {
        if(process_step ==0)
        {
            if(is_img_load && img_list !=0 && img_row !=0)
            {
                //send width & height
                QByteArray send_size(3,0);
                send_size[0] = 0xaa;
                send_size[1] = img_list;
                send_size[2] = img_row;

                tcpSocket->write(send_size.data(),3);
                process_step ++;
            }
        }else{
                tcpSocket->write(dat.data(),len);
        }
    }else{
        log("In send task,no client,playing is not start");
    }
}

void Widget::send_process(void)
{
    qDebug()<<"In send process,0";
    if(process_step ==0)
    {
        if(is_img_load && img_list !=0 && img_row !=0)
        {
            //send width & height
            QByteArray send_size(3,0);
            send_size[0] = 0xaa;
            send_size[1] = img_list;
            send_size[2] = img_row;
            if(tcpSocket != NULL)
                tcpSocket->write(send_size.data(),3);
            process_step ++;
            qDebug()<<"send size";
        }else{
             qDebug()<<"send nothing,1";
        }
    }else{
         qDebug()<<"send nothing,2";
    }
}


void Widget::framechange(void)
{
    unsigned char bitmask[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
    log("frame change:" + QString::number(movie->currentFrameNumber()));
    //scale to fit 12864
    QImage last_img = movie->currentImage().scaledToHeight(64);
    if(last_img.width()>128)
           last_img = last_img.scaledToWidth(128);

    int dat_num=0;
    img_list=last_img.width();
    if((last_img.height() %8)>0)
    {
        img_row = (last_img.height() /8 +1) ;
    }else
        img_row = (last_img.height() /8);
    dat_num = img_row * img_list;

    QByteArray sending_data(1024,0);
    sending_data[0] = 0xab;

    for(int j=0;j<last_img.height();j++)
    {

        for(int i=0;i<last_img.width();i++)
        {
            // |
            // |
            // V
            int y_index = j % 8;
            //----->
            int x_index = j / 8 * last_img.width() + i;
            if(last_img.pixelColor(last_img.width()-1-i,j).value()>100)
            {
                sending_data[x_index+1] = (sending_data[x_index+1] | bitmask[y_index]) & 0x000000ff;
            }
        }

    }
    send_process(sending_data,dat_num);
}

void Widget::log(QString msg)
{
    this->ui->log->append(msg);
}
