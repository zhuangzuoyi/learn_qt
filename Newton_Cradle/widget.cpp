#include "widget.h"
#include "QPainter"
#include "QtGui"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,Qt::white);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400,400);
  //  Circle_point = new QPoint();
    radius = 30;
}

Widget::~Widget()
{

}


void Widget::paintEvent(QPaintEvent *)
{

    QPainter p(this);
    /*
    QRect rect(200,200,250,250);
    QLinearGradient lg(QPointF(200,250),QPointF(250,200));
    lg.setColorAt(0,Qt::white);
    lg.setColorAt(1,Qt::black);
    p.setBrush(lg);
    p.drawEllipse(rect);
    */
    drawCircle(&p);
}


void Widget::mouseMoveEvent(QMouseEvent *e)
{
    qDebug()<<"The mouse's pos is:"<<e->pos().x()<<","<<e->pos().y();
}


void Widget::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"Mouse press:"<<e->pos().x()<<","<<e->pos().y();
    Circle_point.setX(e->pos().x());
    Circle_point.setY(e->pos().y());
    update();

}

void Widget::drawCircle(QPainter *p)
{
    p->save();
    QRect circle_rect;
    QPoint Start_pont,End_point;
    QPoint lg_start,lg_end;
    Start_pont.setX(Circle_point.x() -radius);
    Start_pont.setY(Circle_point.y()-radius);
    End_point.setX(Circle_point.x() +radius);
    End_point.setY(Circle_point.y()+radius);
    /*
    if(Circle_point.x() >radius && Circle_point.y() >radius)
    {
        Start_pont.setX(Circle_point.x() -radius);
        Start_pont.setY(Circle_point.y()-radius);
        End_point.setX(Circle_point.x() +radius);
        End_point.setY(Circle_point.y()+radius);
    }
    else
    {

     //   Start_pont.setX(0);
     //   Start_pont.setY(0);
//        End_point.setX(radius);
     //   End_point.setY(radius);

    }*/
    lg_start.setX(Start_pont.x()+radius);
    lg_start.setY(Start_pont.y());
    lg_end.setX(End_point.x()+radius);
    lg_end.setY(End_point.y());
    QLinearGradient lg(lg_start,lg_end);
    lg.setColorAt(0,Qt::white);
    lg.setColorAt(1,Qt::black);
    p->setBrush(lg);
    circle_rect.setBottomRight(End_point);
    circle_rect.setTopLeft(Start_pont);
    p->drawEllipse(circle_rect);
    p->restore();
}
