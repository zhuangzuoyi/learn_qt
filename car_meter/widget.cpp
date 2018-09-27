#include "widget.h"
#include "QPainter"
#include "QDebug"
#include <QFontDatabase>
#include "QTimer"

#define dial_background_startangle  -45
#define dial_background_spanangle  ( 180- (dial_background_startangle * 2)) * 16
#define DIAL_ONE_START_POINT_X  40
#define DIAL_ONE_START_POINT_Y  40

#define DIAL_SIZE_DIV  8
#define DIAL_SIZE_MUL  7

#define ANGLE_STEP     25

#define SPEED_STEP     2.5

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    const QColor background(0,0,0);
    setPalette(QPalette(background));
    resize(720,720);
    Speed = 0;

    Speed_task = 0;
    Speed_target = 0;
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->start(150);
}

Widget::~Widget()
{

}

void Widget::car_meter_test_task()
{
    if(Speed_task == Speed_target)
    {
        Speed_target = rand() % 100;
    }else if(Speed_task < Speed_target)
    {
        Speed_task ++;
    }else{
        Speed_task --;
    }
    Speed = Speed_task;
}

void Widget::timerUpDate()
{
    car_meter_test_task();
    update();
}

void Widget::dial_background(QPainter *p)
{
    dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
  //  qDebug()<<dial_widht;
  //  qDebug()<<dial_height;
    p->save();
    QRectF rectangle(DIAL_ONE_START_POINT_X, DIAL_ONE_START_POINT_Y, dial_widht,dial_height);
    int startAngle = dial_background_startangle * 16;
  //  qDebug()<<dial_background_spanangle;
    int spanAngle = dial_background_spanangle;
  //  qDebug()<<spanAngle;
    QBrush bursh(QColor(14,28,47));
    p->setBrush(bursh);
    QPen pen(QColor(14,28,47));
    p->setPen(pen);
    p->drawPie(rectangle, startAngle, spanAngle);
    //p->drawRect(rectangle);
    p->restore();
}



void Widget::draw_dial_background_black(QPainter *p)
{
    int dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    int dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
 //   qDebug()<<dial_widht;
 //   qDebug()<<dial_height;
    p->save();
    QRectF rectangle(DIAL_ONE_START_POINT_X+25, DIAL_ONE_START_POINT_Y+25, dial_widht-50,dial_height-50);
    int startAngle = dial_background_startangle * 16;
 //   qDebug()<<dial_background_spanangle;
    int spanAngle = dial_background_spanangle;
 //   qDebug()<<spanAngle;
    QBrush bursh(QColor(0,0,0));
    p->setBrush(bursh);
    QPen pen(QColor(0,0,0));
    p->setPen(pen);
    p->drawPie(rectangle, startAngle, spanAngle);
    p->restore();
}


void Widget::draw_dial_sendond_background(QPainter *p)
{
    int dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    int dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
 //   qDebug()<<dial_widht;
 //   qDebug()<<dial_height;
    p->save();
    QRectF rectangle(DIAL_ONE_START_POINT_X+30, DIAL_ONE_START_POINT_Y+30, dial_widht-60,dial_height-60);
    int startAngle = dial_background_startangle * 16;
//    qDebug()<<dial_background_spanangle;
    int spanAngle = dial_background_spanangle;
 //   qDebug()<<spanAngle;
    QBrush bursh(QColor(24,46,84));
    p->setBrush(bursh);
    QPen pen(QColor(0,0,0));
    p->setPen(pen);
    p->drawPie(rectangle, startAngle, spanAngle);
    p->restore();
}


void Widget::draw_dial_background_gradual(QPainter *p)
{
    int dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    int dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;

 //   qDebug()<<dial_widht;
 //   qDebug()<<dial_height;
    p->save();
    QRectF rectangle(DIAL_ONE_START_POINT_X+50, DIAL_ONE_START_POINT_Y+50, dial_widht-100,dial_height-100);
    int startAngle = dial_background_startangle * 16;
  //  qDebug()<<dial_background_spanangle;
    int spanAngle = dial_background_spanangle;
  //  qDebug()<<spanAngle;
    //QBrush bursh(QColor(24,46,84));
    int focal_x = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    int focal_y = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    QRadialGradient radialGradient(QPointF(focal_x,focal_y),(dial_widht-60) / 2,QPointF(focal_x,focal_y));
    radialGradient.setColorAt(1, QColor(15,27,65));
    radialGradient.setColorAt(0, QColor(0, 0, 0));
    radialGradient.setSpread(QGradient::PadSpread);
    p->setBrush(radialGradient);
    QPen pen(QColor(0,0,0));
    pen.setWidth(0);
    p->setPen(pen);
    p->drawPie(rectangle, startAngle, spanAngle);

    p->restore();
}



void Widget::draw_dial_speed(QPainter *p)
{
    int dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    int dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
   // qDebug()<<dial_widht;
    //qDebug()<<dial_height;
    p->save();
    QRectF rectangle(DIAL_ONE_START_POINT_X+30, DIAL_ONE_START_POINT_Y+30, dial_widht-60,dial_height-60);
    int startAngle = (215- Speed * SPEED_STEP) * 16;//dial_background_startangle * 16;
   // qDebug()<<dial_background_spanangle;
    int spanAngle = Speed * SPEED_STEP * 16;
   // qDebug()<<spanAngle;

    int focal_x = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    int focal_y = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    QRadialGradient radialGradient(QPointF(focal_x,focal_y),(dial_widht-60) / 2,QPointF(focal_x,focal_y));
    radialGradient.setColorAt(1, QColor(58,115,235));
    radialGradient.setColorAt(0.5, QColor(0, 0, 0));
    radialGradient.setSpread(QGradient::PadSpread);
    p->setBrush(radialGradient);

    QPen pen(QColor(0,0,0));
    p->setPen(pen);
    p->drawPie(rectangle, startAngle, spanAngle);
    p->restore();
}



void Widget::draw_dial_show_01(QPainter *p)
{
    int li_01 = 150;

    int dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    int dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    //qDebug()<<dial_widht;
   // qDebug()<<dial_height;
    p->save();
    QRectF rectangle(DIAL_ONE_START_POINT_X+li_01, DIAL_ONE_START_POINT_Y+li_01, dial_widht-li_01*2,dial_height-li_01*2);
    //int startAngle = dial_background_startangle * 16;
    //qDebug()<<dial_background_spanangle;
    int spanAngle = dial_background_spanangle;
    //qDebug()<<spanAngle;

    QBrush bursh(QColor(34,96,253));
    p->setBrush(bursh);
    QPen pen(QColor(34,96,253));
    p->setPen(pen);

    p->drawEllipse(rectangle);
    p->restore();
}

void Widget::draw_dial_show_02(QPainter *p)
{
    int li_01 = 158;

    int dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    int dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    //qDebug()<<dial_widht;
    //qDebug()<<dial_height;
    p->save();
    QRectF rectangle(DIAL_ONE_START_POINT_X+li_01, DIAL_ONE_START_POINT_Y+li_01, dial_widht-li_01*2,dial_height-li_01*2);
    //int startAngle = dial_background_startangle * 16;
    //qDebug()<<dial_background_spanangle;
    int spanAngle = dial_background_spanangle;
    //qDebug()<<spanAngle;

    QBrush bursh(QColor(0,0,0));
    p->setBrush(bursh);
    QPen pen(QColor(0,0,0));
    p->setPen(pen);

    p->drawEllipse(rectangle);
    p->restore();
}


void Widget::draw_dial_speed_text(QPainter *p)
{
    //int t_x=0,t_y=0;
    int x_offset=0,y_offset=0;
    int dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    int dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    //qDebug()<<dial_widht;
    //qDebug()<<dial_height;
    p->save();

    QFont f = p->font();
    f.setWeight(50);
    f.setPointSize(110);
    p->setFont(f);
    int focal_x = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    int focal_y = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    //Speed  = 5;
    if(Speed >= 100)
    {
        x_offset = 130;
        y_offset = 50;
    }else if(Speed >= 10)
    {
        x_offset = 80;
        y_offset = 50;
    }else{
        x_offset = 50;
        y_offset = 50;
    }
    p->drawText(focal_x-x_offset,focal_y+y_offset,QString::number(Speed));
    p->restore();
}


void Widget::draw_dial_tick(QPainter *p)
{
    int tick_start_x=0,tick_start_y=0;
    int tick_end_x=0,tick_end_y=0;
    dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    //qDebug()<<dial_widht;
   // qDebug()<<dial_height;
    //QRectF rectangle(DIAL_ONE_START_POINT_X, DIAL_ONE_START_POINT_Y, dial_widht,dial_height);

    p->save();
    int focal_x = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    int focal_y = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    p->translate(focal_x,focal_y);
    tick_start_y = -( dial_height / 2);
    tick_start_x = 0;
    tick_end_y =  -(dial_height / 2 - 25);
    tick_end_x = 0;
    QPen pen=QPen(QColor(0,246,255));
    pen.setWidth(5);
    p->setPen(pen);
    p->rotate(-125) ;
    p->drawLine(tick_start_x,tick_start_y,tick_end_x,tick_end_y);
    for(int i=0;i<10;i++)
    {
        p->rotate(25);
        p->drawLine(tick_start_x,tick_start_y,tick_end_x,tick_end_y);
    }
    p->restore();
}

void Widget::draw_dial_tick_02(QPainter *p)
{
    //52,115,128
    int tick_start_x=0,tick_start_y=0;
    int tick_end_x=0,tick_end_y=0;
    dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
   // qDebug()<<dial_widht;
   // qDebug()<<dial_height;
    //QRectF rectangle(DIAL_ONE_START_POINT_X, DIAL_ONE_START_POINT_Y, dial_widht,dial_height);

    p->save();
    int focal_x = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    int focal_y = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    p->translate(focal_x,focal_y);
    tick_start_y = -( dial_height / 2)+5;
    tick_start_x = 0;
    tick_end_y =  -(dial_height / 2 - 25)-5;
    tick_end_x = 0;
    QPen pen=QPen(QColor(52,115,128));
    pen.setWidth(4);
    p->setPen(pen);
    p->rotate(-112.5) ;
    //p->drawLine(tick_start_x,tick_start_y,tick_end_x,tick_end_y);
    for(int i=0;i<10;i++)
    {
        p->drawLine(tick_start_x,tick_start_y,tick_end_x,tick_end_y);
        p->rotate(25);

    }
    p->restore();
}


void Widget::draw_dial_scale(QPainter *p)
{
    int scale_start_x=0,scale_start_y=0;
    int radius = 0;
    float rad = 3.14/180.0;
    dial_height  = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;
    dial_widht   = width() / DIAL_SIZE_DIV * DIAL_SIZE_MUL;

    p->save();
    int focal_x = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    int focal_y = (dial_widht-100) / 2 + DIAL_ONE_START_POINT_X+50;
    p->translate(focal_x,focal_y);
    /*
    scale_start_y = -( dial_height / 2);
    scale_start_x = 0;
    tick_end_y =  -(dial_height / 2 - 25);
    tick_end_x = 0;
    */
    radius = (dial_widht-60) / 2;

    QPen pen=QPen(QColor(255,246,255));
    //pen.setWidth(5);
    p->setPen(pen);

    QFont f = p->font();
    f.setPointSize(30);
    p->setFont(f);
    float start_ang = 315.0;
    float at_ang = 0;
    scale_start_x = sin((double)(start_ang * rad)) * radius;
    scale_start_y = cos((double)(start_ang* rad)) * radius;
    p->drawText(scale_start_x-20,scale_start_y-25,"0");

    //10
    int i=0;
    at_ang = start_ang - 25 ;
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x-10,scale_start_y-30,QString::number(10));

    //20
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x+10,scale_start_y-30,QString::number((i+1) * 10));

    //30
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x+20,scale_start_y-10,QString::number((i+1) * 10));

    //40
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x+20,scale_start_y+5,QString::number((i+1) * 10));

    //50
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x+25,scale_start_y+25,QString::number((i+1) * 10));


    //60
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x+15,scale_start_y+50,QString::number((i+1) * 10));


    //70
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x-10,scale_start_y+60,QString::number((i+1) * 10));


    //80
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x-30,scale_start_y+70,QString::number((i+1) * 10));

    //90
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x-50,scale_start_y+70,QString::number((i+1) * 10));


    //100
    i ++;
    at_ang = start_ang - 25 * (i+1);
    scale_start_x = sin((double)(at_ang * rad)) * radius;
    scale_start_y = cos((double)(at_ang* rad)) * radius;
    p->drawText(scale_start_x-95,scale_start_y+50,QString::number((i+1) * 10));


    p->restore();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    dial_background(&p);
    draw_dial_background_black(&p);
    draw_dial_sendond_background(&p);
    draw_dial_background_gradual(&p);
    draw_dial_speed(&p);
    draw_dial_show_01(&p);
    draw_dial_show_02(&p);
    draw_dial_speed_text(&p);
    draw_dial_tick(&p);
    draw_dial_tick_02(&p);
    draw_dial_scale(&p);
}
