#include "widget.h"
#include "QPainter"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    const QColor background(45,45,46);
    setPalette(QPalette(background));
    setAutoFillBackground(true);

    resize(400,400);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    drawpic(&p);
    drawCover(&p);
}


void Widget::drawCover(QPainter *p)
{
    p->save();
    QPen pen(QColor(45,45,46));
    //QPen pen(Qt::white);
    pen.setWidth(120);
    p->setPen(pen);
    p->drawArc(0,0,width(),height(),0*16,360*16);
    p->restore();
}


void Widget::drawpic(QPainter *p)
{
    p->save();
    QPixmap pix;
    pix.load("../round_head/001.jpg");
    int pix_x =  width() / 2 - pix.width() /2;
    int pix_y = height() /2 - pix.height() /2 ;
    p->drawPixmap(pix_x, pix_y, pix);
    p->restore();
}
