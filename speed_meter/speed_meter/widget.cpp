#include "widget.h"
#include "QPainter"
#include "QtGui"
#include "QFont"
#include "QTimer"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    const QColor background(45,45,46);
    setPalette(QPalette(background));
    setAutoFillBackground(true);
    setMinimumSize(400,400);
    rect_size = 350;
    rect_s_x = 50;;
    rect_s_y=50;
    setMinimumSize(rect_size+100,rect_size/2+100);
    resize(rect_size+100,rect_size/2+100);
    loop_size = 150;
    Speed = 0;
    flag =0;
     QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, updateValue);
    timer->start(50);
}


void Widget::updateValue(void)
{
    if(flag==0)
    {
        Speed +=1;
        if(Speed ==50)
            flag =1;
    }else{
        Speed -=1;
        if(Speed == 0)
            flag =0;
    }

    update();
}


Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    //drawrect(&p);
    drawLoop(&p);
    drawSector(&p);
    drawInterLoop(&p);
    drawSector_cut(&p);
    paintTitle(&p);
    paintSpeed(&p);
    paintUnit(&p);
}


void Widget::paintTitle(QPainter *p)
{
    p->save();
    QFont font;
    font.setPixelSize(30);
    //font.setPointSize(50);
    p->setFont(font);
    p->drawText(rect_s_x+ rect_size/2-30,100-60,"速度");
    p->restore();
}

void Widget::paintSpeed(QPainter *p)
{
    QString Speed_str;
    Speed_str.setNum(Speed);
    p->save();
    QFont font;
    font.setPixelSize(30);
    //font.setPointSize(50);
    p->setFont(font);
    p->drawText(rect_s_x+ rect_size/2-15,rect_s_y+ loop_size,Speed_str);
    p->restore();
}


void Widget::paintUnit(QPainter *p)
{
    p->save();
    QFont font;
    font.setPixelSize(20);
    //font.setPointSize(50);
    p->setFont(font);
    p->drawText(rect_s_x+ rect_size/2-10,rect_s_y+ loop_size+30,"KM/H");

    p->restore();
}


void Widget::drawLoop(QPainter *p)
{
    p->save();
    QBrush bursh(QColor(80,80,83));
    p->setBrush(bursh);
   QRect rect(rect_s_x,rect_s_y,rect_size,rect_size);
    p->drawChord(rect,0*16,180*16);
    p->restore();
}


void Widget::drawInterLoop(QPainter *p)
{
     int half_size = loop_size/2;
    p->save();
    QBrush bursh(QColor(45,45,46));
    p->setBrush(bursh);
   QRect rect(rect_s_x+half_size,rect_s_y+half_size,rect_size-loop_size,rect_size-loop_size);
    p->drawChord(rect,0*16,180*16);
    p->restore();
}



void Widget::drawSector(QPainter *p)
{
    float Sector_start_arc =180 -  Speed * 1.8;
    float Sector_end_arc =  180;
    qDebug()<<"Sector:"<<Sector_start_arc<<","<<Sector_end_arc<<"Speed"<<Speed;
    p->save();
    QBrush bursh(QColor(85,191,59));
    p->setBrush(bursh);
   QRect rect(rect_s_x,rect_s_y,rect_size,rect_size);
    p->drawChord(rect,Sector_start_arc*16,Sector_end_arc*16);
    p->restore();
}

void Widget::drawSector_cut(QPainter *p)
{
    p->save();
    QPen pen(QColor(45,45,46));
    pen.setStyle(Qt::CustomDashLine);
   // pen.setColor();
    QRect rect(0,rect_s_y+rect_size/2,500,500);
    QBrush bursh(QColor(45,45,46));
    p->setBrush(bursh);
    p->setPen(pen);
    p->drawRect(rect);
    p->restore();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"Mouse Press:"<<e->pos().x()<<","<<e->pos().y();
}


void Widget::drawrect(QPainter *p)
{

    p->save();
    QBrush bursh(Qt::white);
    p->setBrush(bursh);
    QRect rect(rect_s_x,rect_s_y,rect_size,rect_size);
    p->drawRect(rect);
    p->restore();
}
