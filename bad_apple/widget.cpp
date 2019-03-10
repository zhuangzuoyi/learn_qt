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
    this->ui->openbtn->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));

    this->ui->bt1->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
    this->ui->bt2->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
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
}

void Widget::newClientConnect(void)
{
    qDebug() << "new client connect";
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disConnect()));

    //init
    process_step =0;
//    send_process();
    if(is_img_load)
    {
        current_frame_index =0;
        movie->jumpToFrame(current_frame_index);
    }
}

void Widget::readMessage()
{
    qDebug() << "read client message";
    QByteArray buf;
    buf = tcpSocket->readAll();
//    qDebug() << buf;
    qDebug()<<"Received data"<<buf;
    if(buf.startsWith("GET_SIZE:OK"))
    {
        qDebug()<<"jump to frame 0";
        current_frame_index ++;
        movie->jumpToFrame(current_frame_index);
    }else if(buf.startsWith("GET_DAT:OK"))
    {
        if(current_frame_index < movie->frameCount())
        {
            current_frame_index ++;
            movie->jumpToFrame(current_frame_index);
        }

    }
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

void Widget::on_openbtn_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open a Movie"));
   if(fileName.isEmpty())
       return;
   movie->setFileName(fileName);
   qDebug()<<movie->frameCount();
   is_img_load = true;
   process_step =0;
   movie->jumpToFrame(current_frame_index);

}

void Widget::on_bt1_clicked()
{
    if(current_frame_index >0)
        current_frame_index --;
    movie->jumpToFrame(current_frame_index);

}

void Widget::on_bt2_clicked()
{
    if(current_frame_index < movie->frameCount())
        current_frame_index ++;
    movie->jumpToFrame(current_frame_index);
}

void Widget::send_process(QByteArray dat,int len)
{
    qDebug()<<"In send process";
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
            qDebug()<<"send nothing";
            qDebug()<<is_img_load;
            qDebug()<<img_list;
            qDebug()<<img_row;
        }
    }else{
            if(tcpSocket != NULL)
                tcpSocket->write(dat.data(),len);//datagram.length());
            qDebug()<<"send dat";
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

    qDebug()<<"frame change"<<movie->currentImage().width()<<movie->currentImage().height();

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
    qDebug()<<"After Scale:"<<last_img.height()<<last_img.width()<<dat_num;

    QString line;
    line.clear();

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
            if(last_img.pixelColor(i,j).value()<100)
            {
                line.append(' ');
            }
            else
            {
                line.append('*');
                sending_data[x_index+1] = (sending_data[x_index+1] | bitmask[y_index]) & 0x000000ff;
            }
        }
        line.append("\r\n");
    }
    ui->Showgif->setText(line);
    send_process(sending_data,dat_num);
}


