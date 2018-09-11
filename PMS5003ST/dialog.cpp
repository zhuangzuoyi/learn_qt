#include "dialog.h"
#include "ui_dialog.h"
#include <QtNetWork>
#include "QDebug"
#include "QDate"

#define Y_MARGIN 10
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    QFile qssfile("base.qss");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();
    this->setStyleSheet(qss);
    ui->setupUi(this);
    //
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(read_message()));//connected()
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(tcp_connected()));
    ui->hcho->setMode(QLCDNumber::Dec);
   // ui->hcho->se
    ui->temp->setMode(QLCDNumber::Dec);
    ui->hum->setMode(QLCDNumber::Dec);

    chart_init();

    /*
    QString sample_time = date_str.mid(11,2)+date_str.mid(14,2)+date_str.mid(17,2);
    qDebug()<<date_str;
    qDebug()<<"The filename is:"<<filename+","+"Sample time:"+sample_time;
    */
    save_count = 0;
    source_flag=0;
}


void Dialog::chart_init(void)
{
    max_dat_y=0;
    pm10_max_dat_y = 0;
    pm1_max_dat_y=0;
    pm25_max_dat_y=0;
    hcho_max_dat_y=0;
    hum_max_dat_y=0;
    //temp
    maxSize = 31; // 只存储最新的 31 个数据
    maxX = 300;
    maxY = 50;
    splineSeries = new QSplineSeries();
    scatterSeries = new QScatterSeries();
    scatterSeries->setMarkerSize(8);
    chart = new QChart();
    chart->addSeries(splineSeries);
    chart->addSeries(scatterSeries);
    chart->legend()->hide();
    chart->setTitle("温度实时曲线");
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 300);
    chart->axisY()->setRange(0, maxY);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->temp_layout->setContentsMargins(0, 0, 0, 0);
    ui->temp_layout->addWidget(chartView);
    //
    pm1_maxSize = 31; // 只存储最新的 31 个数据
    pm1_maxX = 300;
    pm1_maxY = 50;
    pm1_splineSeries = new QSplineSeries();
    pm1_scatterSeries = new QScatterSeries();
    pm1_scatterSeries->setMarkerSize(8);
    pm1_chart = new QChart();
    pm1_chart->addSeries(pm1_splineSeries);
    pm1_chart->addSeries(pm1_scatterSeries);
    pm1_chart->legend()->hide();
    pm1_chart->setTitle("PM1.0");
    pm1_chart->createDefaultAxes();
    pm1_chart->axisX()->setRange(0, 300);
    pm1_chart->axisY()->setRange(0, pm1_maxY);
    pm1_chartView = new QChartView(pm1_chart);
    pm1_chartView->setRenderHint(QPainter::Antialiasing);
    ui->pm1_layout->setContentsMargins(0, 0, 0, 0);
    ui->pm1_layout->addWidget(pm1_chartView);
    //PM2.5
    pm25_maxSize = 31; // 只存储最新的 31 个数据
    pm25_maxX = 300;
    pm25_maxY = 50;
    pm25_splineSeries = new QSplineSeries();
    pm25_scatterSeries = new QScatterSeries();
    pm25_scatterSeries->setMarkerSize(8);
    pm25_chart = new QChart();
    pm25_chart->addSeries(pm25_splineSeries);
    pm25_chart->addSeries(pm25_scatterSeries);
    pm25_chart->legend()->hide();
    pm25_chart->setTitle("PM2.5");
    pm25_chart->createDefaultAxes();
    pm25_chart->axisX()->setRange(0, 300);
    pm25_chart->axisY()->setRange(0, pm25_maxY);
    pm25_chartView = new QChartView(pm25_chart);
    pm25_chartView->setRenderHint(QPainter::Antialiasing);
    ui->pm25_layout->setContentsMargins(0, 0, 0, 0);
    ui->pm25_layout->addWidget(pm25_chartView);
    //PM10
    pm10_maxSize = 31; // 只存储最新的 31 个数据
    pm10_maxX = 300;
    pm10_maxY = 50;
    pm10_splineSeries = new QSplineSeries();
    pm10_scatterSeries = new QScatterSeries();
    pm10_scatterSeries->setMarkerSize(8);
    pm10_chart = new QChart();
    pm10_chart->addSeries(pm10_splineSeries);
    pm10_chart->addSeries(pm10_scatterSeries);
    pm10_chart->legend()->hide();
    pm10_chart->setTitle("PM10");
    pm10_chart->createDefaultAxes();
    pm10_chart->axisX()->setRange(0, 300);
    pm10_chart->axisY()->setRange(0, pm10_maxY);
    pm10_chartView = new QChartView(pm10_chart);
    pm10_chartView->setRenderHint(QPainter::Antialiasing);
    ui->pm10_layout->setContentsMargins(0, 0, 0, 0);
    ui->pm10_layout->addWidget(pm10_chartView);
    //hoco
    hcho_maxSize = 31; // 只存储最新的 31 个数据
    hcho_maxX = 300;
    hcho_maxY = 50;
    hcho_splineSeries = new QSplineSeries();
    hcho_scatterSeries = new QScatterSeries();
    hcho_scatterSeries->setMarkerSize(8);
    hcho_chart = new QChart();
    hcho_chart->addSeries(hcho_splineSeries);
    hcho_chart->addSeries(hcho_scatterSeries);
    hcho_chart->legend()->hide();
    hcho_chart->setTitle("温度实时曲线");
    hcho_chart->createDefaultAxes();
    hcho_chart->axisX()->setRange(0, 300);
    hcho_chart->axisY()->setRange(0, hcho_maxY);
    hcho_chartView = new QChartView(hcho_chart);
    hcho_chartView->setRenderHint(QPainter::Antialiasing);
    ui->hcho_layout->setContentsMargins(0, 0, 0, 0);
    ui->hcho_layout->addWidget(hcho_chartView);
    //hum
    hum_maxSize = 31; // 只存储最新的 31 个数据
    hum_maxX = 300;
    hum_maxY = 50;
    hum_splineSeries = new QSplineSeries();
    hum_scatterSeries = new QScatterSeries();
    hum_scatterSeries->setMarkerSize(8);
    hum_chart = new QChart();
    hum_chart->addSeries(hum_splineSeries);
    hum_chart->addSeries(hum_scatterSeries);
    hum_chart->legend()->hide();
    hum_chart->setTitle("温度实时曲线");
    hum_chart->createDefaultAxes();
    hum_chart->axisX()->setRange(0, 300);
    hum_chart->axisY()->setRange(0, hum_maxY);
    hum_chartView = new QChartView(hum_chart);
    hum_chartView->setRenderHint(QPainter::Antialiasing);
    ui->hum_layout->setContentsMargins(0, 0, 0, 0);
    ui->hum_layout->addWidget(hum_chartView);

}
void Dialog::tcp_connected()
{
    qDebug("connected to server\r\n");
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::tcp_connect()
{
    //blockSize = 0; //初始化其为0
    tcpSocket->abort(); //取消已有的连接
    tcpSocket->connectToHost(ui->host_ip->text(),ui->host_port->text().toInt());
    qDebug("connect even");
        //连接到主机，这里从界面获取主机地址和端口号
}


void Dialog::seve_data(QString filename,QString Dat)
{
    save_count ++;
    if(save_count == 10)
    {
        qDebug("save data................");
        save_count =0;
        QFile f(filename);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            qDebug("open failed");
            return ;
        }
        QTextStream txt_output(&f);
        txt_output<<Dat<<endl;
        txt_output.flush();
        f.close();
        qDebug("save end................");
    }
}

void Dialog::Save_source_data(QString filename,QByteArray dat)
{
    source_flag++;
    if(source_flag == 10)
    {
        source_flag = 0;
        QFile file(filename+".dat");
        if(!file.open(QIODevice::WriteOnly |  QIODevice::Append))
        {
            qDebug("open failed");
            return ;
        }
        QDataStream out(&file);
        out << dat;
        file.close();
    }
}
/*
 *     void (uint16_t dat);
    void (uint16_t dat);
    void (uint16_t dat);
    void (uint16_t dat);
    void (uint16_t dat);
    */
void Dialog::read_message()
{
    if(tcpSocket->bytesAvailable()>0)
    {
        QByteArray re_temp=tcpSocket->readAll();
        char *received = re_temp.data();
        //qDebug("byte avaliable:%d",received.length());//;
        if(received[0] == 0x42 && received[1] == 0x4d && received[3] == 0x24 && re_temp.length()== 40)
        {
            uint16_t check=0,i=0;
            uint16_t temp=0;
            QTime current_time = QTime::currentTime();
            int sample_senond = current_time.msecsSinceStartOfDay();// /1000;
            qDebug("The time is:%d",sample_senond);
           // os_printf("get PMS5003ST data\r\n");
            for(i=0;i<38;i++)
            {
            check += received[i];
            }
            //show in lcd

            QString seve_para=QString::number(sample_senond,10);
            //PM1.0
            temp = (received[10] <<8) | (unsigned char)received[11];
           // qDebug("The PM1.0 is:%d\r\n",temp);
            ui->PM10->display(temp);
            pm1_update(temp);
            seve_para += ",PM1:"+QString::number(temp,10);
            //save_para

            //PM2.5
            temp = (received[12] <<8) | (unsigned char)received[13];
           // qDebug("The PM2.5 is:%d\r\n",temp);
            ui->PM25->display(temp);
            pm25_update(temp);
            seve_para += ",PM2.5:"+QString::number(temp,10);

            //PM1
            temp = (received[14] <<8) | (unsigned char)received[15];
            //qDebug("The PM10 is:%d\r\n",temp);
             ui->PM1->display(temp);
            pm10_update(temp);
            seve_para += ",PM10:"+QString::number(temp,10);

            //HCHO
            temp = (received[28] <<8) | (unsigned char)received[29];
           // qDebug("The HCHO is:%d\r\n",temp);
            this->ui->hcho->display(temp/1000.0);
            hcho_update(temp);
            seve_para += ",hcho:"+QString::number(temp,10);

            //Temp
            temp = ((received[30] & 0xff) << 8)  + (unsigned int) received[31];

            temp = (received[30] << 8) ;
            temp += (unsigned char)received[31];
            //qDebug("The temp is:%d\r\n",temp);
            qDebug("The 30 byte is:%d",(received[30] & 0xff) * 0xff);
            this->ui->temp->display(temp/10.0);
            temp_update(temp/10.0);
            seve_para += ",TEM:"+QString::number(temp,10);



            temp = (received[32] << 8) ;
            temp += (unsigned char)received[33];
            //qDebug("The hum is:%f\r\n",temp/10.0);
            qDebug("The 32 byte is:%d",(received[32] & 0xff) * 0xff);
            this->ui->hum->display(temp/10.0);
            hum_update(temp/10);

            seve_para += ",HUM:"+QString::number(temp,10);
            qDebug()<<seve_para;

            QDateTime current_date = QDateTime::currentDateTime();
            QString date_str = current_date.toString("yyyy.MM.dd hh:mm:ss");
            qDebug()<<date_str;
            QString filename = date_str.mid(2,2)+date_str.mid(5,2)+date_str.mid(8,2);
            qDebug()<<filename;
            seve_data(filename,seve_para);
            Save_source_data(filename,re_temp);
        }
    }
}

void Dialog::tcp_send()
{
    char send_data[]="hello\r\n";
    tcpSocket->write(send_data,sizeof(send_data));
}

void Dialog::on_tcp_send_clicked()
{
    tcp_send();
}

void Dialog::on_tcp_connect_clicked()
{
    tcp_connect();
}

void Dialog::temp_update(uint16_t dat)
{
    if(max_dat_y < dat)
        max_dat_y = dat;
    if(maxY <( max_dat_y+ Y_MARGIN))
    {
        maxY = max_dat_y+ Y_MARGIN;
        chart->axisY()->setRange(0, maxY);
    }

    data << dat;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (data.size() > maxSize) {
        data.removeFirst();
    }
    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        splineSeries->clear();
        scatterSeries->clear();
        int dx = maxX / (maxSize-1);
        int less = maxSize - data.size();
        for (int i = 0; i < data.size(); ++i) {
            splineSeries->append(less*dx+i*dx, data.at(i));
            scatterSeries->append(less*dx+i*dx, data.at(i));
        }
    }
}


void Dialog::hum_update(uint16_t dat)
{
    if(hum_max_dat_y < dat)
        hum_max_dat_y = dat;

    if(hum_maxY <( hum_max_dat_y+ Y_MARGIN))
    {
        hum_maxY = hum_max_dat_y+ Y_MARGIN;
        hum_chart->axisY()->setRange(0, hum_maxY);
    }

    hum_data << dat;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (hum_data.size() > hum_maxSize) {
        hum_data.removeFirst();
    }
    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        hum_splineSeries->clear();
        hum_scatterSeries->clear();
        int dx = hum_maxX / (hum_maxSize-1);
        int less = hum_maxSize - hum_data.size();
        for (int i = 0; i < hum_data.size(); ++i) {
            hum_splineSeries->append(less*dx+i*dx, hum_data.at(i));
            hum_scatterSeries->append(less*dx+i*dx, hum_data.at(i));
        }
    }
}

void Dialog::hcho_update(uint16_t dat)
{
    if(hcho_max_dat_y < dat)
        hcho_max_dat_y = dat;

    if(hcho_maxY <( hcho_max_dat_y+ Y_MARGIN))
    {
        hcho_maxY = hcho_max_dat_y+ Y_MARGIN;
        hcho_chart->axisY()->setRange(0, hcho_maxY);
    }

    hcho_data << dat;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (hcho_data.size() > hcho_maxSize) {
        hcho_data.removeFirst();
    }
    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        hcho_splineSeries->clear();
        hcho_scatterSeries->clear();
        int dx = hcho_maxX / (hcho_maxSize-1);
        int less = hcho_maxSize - hcho_data.size();
        for (int i = 0; i < hcho_data.size(); ++i) {
            hcho_splineSeries->append(less*dx+i*dx, hcho_data.at(i));
            hcho_scatterSeries->append(less*dx+i*dx, hcho_data.at(i));
        }
    }
}

void Dialog::pm1_update(uint16_t dat)
{
    if(pm1_max_dat_y < dat)
        pm1_max_dat_y = dat;

    if(pm1_maxY <( pm1_max_dat_y+ Y_MARGIN))
    {
        pm1_maxY = pm1_max_dat_y+ Y_MARGIN;
        pm1_chart->axisY()->setRange(0, pm1_maxY);
    }

    pm1_data << dat;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (pm1_data.size() > pm1_maxSize) {
        pm1_data.removeFirst();
    }
    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        pm1_splineSeries->clear();
        pm1_scatterSeries->clear();
        int dx = pm1_maxX / (pm1_maxSize-1);
        int less = pm1_maxSize - pm1_data.size();
        for (int i = 0; i < pm1_data.size(); ++i) {
            pm1_splineSeries->append(less*dx+i*dx, pm1_data.at(i));
            pm1_scatterSeries->append(less*dx+i*dx, pm1_data.at(i));
        }
    }
}


void Dialog::pm25_update(uint16_t dat)
{
    if(pm25_max_dat_y < dat)
        pm25_max_dat_y = dat;
    if(pm25_maxY <( pm25_max_dat_y+ Y_MARGIN))
    {
        pm25_maxY = pm25_max_dat_y+ Y_MARGIN;
        pm25_chart->axisY()->setRange(0, pm25_maxY);
    }
    pm25_data << dat;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (pm25_data.size() > pm25_maxSize) {
        pm25_data.removeFirst();
    }
    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        pm25_splineSeries->clear();
        pm25_scatterSeries->clear();
        int dx = pm25_maxX / (pm25_maxSize-1);
        int less = pm25_maxSize - pm25_data.size();
        for (int i = 0; i < pm25_data.size(); ++i) {
            pm25_splineSeries->append(less*dx+i*dx, pm25_data.at(i));
            pm25_scatterSeries->append(less*dx+i*dx, pm25_data.at(i));
        }
    }
}


void Dialog::pm10_update(uint16_t dat)
{
    if(pm10_max_dat_y < dat)
        pm10_max_dat_y = dat;
    if(pm10_maxY <( pm10_max_dat_y+ Y_MARGIN))
    {
        pm10_maxY = pm10_max_dat_y+ Y_MARGIN;
        pm10_chart->axisY()->setRange(0, pm10_maxY);
    }
    pm10_data << dat;
    // 数据个数超过了最大数量，则删除最先接收到的数据，实现曲线向前移动
    while (pm10_data.size() > pm10_maxSize) {
        pm10_data.removeFirst();
    }
    // 界面被隐藏后就没有必要绘制数据的曲线了
    if (isVisible()) {
        pm10_splineSeries->clear();
        pm10_scatterSeries->clear();
        int dx = pm10_maxX / (pm10_maxSize-1);
        int less = pm10_maxSize - pm10_data.size();
        for (int i = 0; i < pm10_data.size(); ++i) {
            pm10_splineSeries->append(less*dx+i*dx, pm10_data.at(i));
            pm10_scatterSeries->append(less*dx+i*dx, pm10_data.at(i));
        }
    }
}
