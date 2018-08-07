#include "widget.h"
#include "QPainter"
#include "QtGui"
#include "QDebug"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background,Qt::white);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400,400);
    canvas_width = 640;
    canvas_height = 480;
    resize(640,480);
    radius = 30;
    ball_num = 5;
    qDebug()<<"Size is:"<<width()<<","<<height();
    up_blank = 80;
    down_blank = 100;
    moving_ball = 0;
    fall_flag = 0;
    fall_step = 1;
    newton_cradle_init();

    timer_interval = 50;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this,SLOT(timeout()));
    timer->setInterval(timer_interval);
}


void Widget::timeout()
{
    int left_start = (width() - radius * 2 * (ball_num-1)) / 2;
    int y_temp,x_temp;

    if(fall_flag ==1)
    {

        x_temp = (moving_point_old.x() - first_ball_original_centor.x()) * (moving_point_old.x() - first_ball_original_centor.x());
        y_temp = sqrt(line_len * line_len -x_temp);
        y_temp += up_blank;
        if((moving_point_old.x()+fall_step) < first_ball_original_centor.x() )
            moving_point_old.setX(moving_point_old.x()+fall_step);
        else
            moving_point_old.setX(first_ball_original_centor.x() );
        moving_point_old.setY(y_temp);

        first_ball_center.setX(moving_point_old.x());
        first_ball_center.setY(moving_point_old.y());
        first_line_end.setX(moving_point_old.x());
        first_line_end.setY(moving_point_old.y());
        fall_step ++;
        if(moving_point_old.x() >= left_start)
        {
            qDebug()<<"change ball";

            fall_flag = 2;
            moving_point_old.setX(firth_ball_center.x());
            moving_point_old.setY(firth_ball_center.y());
        }
    }else if(fall_flag ==2)
    {
        x_temp =  (moving_point_old.x() - firth_ball_original_centor.x()) * (moving_point_old.x() - firth_ball_original_centor.x());
        y_temp = sqrt(line_len * line_len - x_temp);
        y_temp += up_blank;
        moving_point_old.setX(moving_point_old.x()+fall_step);
        moving_point_old.setY(y_temp);

        firth_ball_center.setX(moving_point_old.x());
        firth_ball_center.setY(moving_point_old.y());
        firth_line_end.setX(moving_point_old.x());
        firth_line_end.setY(moving_point_old.y());
        fall_step --;
        if(moving_point_old.x() >= (firth_ball_original_centor.x() + moving_max))
        {
            fall_flag = 3;
            fall_step = 1;
        }
    }else if(fall_flag ==3)
    {
        x_temp =  (moving_point_old.x() - firth_ball_original_centor.x()) * (moving_point_old.x() - firth_ball_original_centor.x());
        y_temp = sqrt(line_len * line_len - x_temp);
        y_temp += up_blank;
        if((moving_point_old.x()-fall_step) > firth_ball_original_centor.x())
        moving_point_old.setX(moving_point_old.x()-fall_step);
        else
            moving_point_old.setX(firth_ball_original_centor.x());
        moving_point_old.setY(y_temp);

        firth_ball_center.setX(moving_point_old.x());
        firth_ball_center.setY(moving_point_old.y());
        firth_line_end.setX(moving_point_old.x());
        firth_line_end.setY(moving_point_old.y());
        fall_step ++;
        if(moving_point_old.x() <= firth_ball_original_centor.x())
        {
            fall_flag = 4;
            moving_point_old.setX(first_ball_center.x());
            moving_point_old.setY(first_ball_center.y());
        }
    }else if(fall_flag ==4)
    {
        x_temp = (moving_point_old.x() - first_ball_original_centor.x()) * (moving_point_old.x() - first_ball_original_centor.x());
        y_temp = sqrt(line_len * line_len -x_temp);
        y_temp += up_blank;
        moving_point_old.setX(moving_point_old.x()-fall_step);
        moving_point_old.setY(y_temp);

        first_ball_center.setX(moving_point_old.x());
        first_ball_center.setY(moving_point_old.y());
        first_line_end.setX(moving_point_old.x());
        first_line_end.setY(moving_point_old.y());
        fall_step --;
        if(moving_point_old.x() <= (first_ball_original_centor.x() - moving_max))
        {
            fall_flag = 1;
            fall_step = 1;
        }
    }

    update();
    qDebug()<<"timeout"<<moving_point_old.x()<<","<<moving_point_old.y();
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    qDebug()<<"The mouse's pos is:"<<e->pos().x()<<","<<e->pos().y();
    if(e->pos().y() > (height() - down_blank - radius))
        return;
    if(moving_ball ==1)
    {
        //the moving ball is the first ball
        if(e->pos().x() < first_ball_original_centor.x())
        {
            moving_point_old.setX(e->pos().x());
            moving_point_old.setY(e->pos().y());
            first_ball_center.setX(moving_point_old.x());
            first_ball_center.setY(moving_point_old.y());
            first_line_end.setX(moving_point_old.x());
            first_line_end.setY(moving_point_old.y());
        }
        if(e->pos().x() < 0)
        {
            moving_max = qAbs(moving_point_old.x() - first_ball_original_centor.x());
            fall_flag = 1;
            moving_ball =0;
             timer->start();
        }
    }else if(moving_ball == 2)
    {
        //the moving ball is the firth ball

        if(e->pos().x() > firth_ball_original_centor.x())
        {
            moving_point_old.setX(e->pos().x());
            moving_point_old.setY(e->pos().y());
            firth_ball_center.setX(moving_point_old.x());
            firth_ball_center.setY(moving_point_old.y());
            firth_line_end.setX(moving_point_old.x());
            firth_line_end.setY(moving_point_old.y());
        }
        qDebug()<<"moving the last ball";
        if(e->pos().x() > width())
        {
            moving_max =qAbs(moving_point_old.x() - firth_ball_original_centor.x());
            fall_flag = 3;
            moving_ball =0;
             timer->start();
        }
    }
    qDebug()<<"update";
    update();
}

void Widget::mouseReleaseEvent(QMouseEvent *)
{
 if(moving_ball ==1)
 {
    moving_max = qAbs(moving_point_old.x() - first_ball_original_centor.x());
    fall_flag = 1;
 }else if(moving_ball ==2)
 {
     moving_max =qAbs(moving_point_old.x() - firth_ball_original_centor.x());
     fall_flag = 3;
 }
 if(fall_flag !=0)
    timer->start();
}


void Widget::mousePressEvent(QMouseEvent *e)
{
    int f_x_abs,f_y_abs;
    int l_x_abs,l_y_abs;

    qDebug()<<"Mouse press:"<<e->pos().x()<<","<<e->pos().y();

    f_x_abs = qAbs(first_ball_center.x() - e->pos().x());
    f_y_abs = qAbs(first_ball_center.y() - e->pos().y());

    l_x_abs = qAbs(firth_ball_center.x() - e->pos().x());
    l_y_abs = qAbs(firth_ball_center.y() - e->pos().y());

    if(f_x_abs < radius && f_y_abs < radius )
    {
        moving_ball = 1;
        moving_point_old.setX(first_ball_original_centor.x());
        moving_point_old.setY(first_ball_original_centor.y());
        if(firth_ball_center.x() != firth_ball_original_centor.x() || firth_ball_center.y() != firth_ball_original_centor.y())
        {
            firth_ball_center.setX(firth_ball_original_centor.x());
            firth_ball_center.setY(firth_ball_original_centor.y());
            firth_line_end.setX(firth_ball_original_centor.x());
            firth_line_end.setY(firth_ball_original_centor.y());

        }
    }else if(l_x_abs < radius && l_y_abs <radius)
    {
        moving_ball = 2;
        moving_point_old.setX(firth_ball_original_centor.x());
        moving_point_old.setY(firth_ball_original_centor.y());
        if(first_ball_center.x() != first_ball_original_centor.x() || first_ball_center.y() != first_ball_original_centor.y())
        {
            first_ball_center.setX(first_ball_original_centor.x());
            first_ball_center.setY(first_ball_original_centor.y());
            first_line_end.setX(first_ball_original_centor.x());
            first_line_end.setY(first_ball_original_centor.y());
        }
    }else{
        moving_ball =0;
    }
    if(moving_ball !=0)
    {
        timer->stop();
        fall_flag = 0;
    }
}



Widget::~Widget()
{

}

void Widget::drawFirst_ball(QPainter *p)
{
    p->save();
    QRect circle_rect;
    QPoint Start_pont,End_point;
    QPoint lg_start,lg_end;
    Start_pont.setX(first_ball_center.x() -radius);
    Start_pont.setY(first_ball_center.y()-radius);
    End_point.setX(first_ball_center.x() +radius);
    End_point.setY(first_ball_center.y()+radius);

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

    p->drawLine(first_line_start,first_line_end);
    p->drawEllipse(circle_rect);
    p->restore();
}

void Widget::drawSecond_ball(QPainter *p)
{
    p->save();
    QRect circle_rect;
    QPoint Start_pont,End_point;
    QPoint lg_start,lg_end;
    Start_pont.setX(second_ball_center.x() -radius);
    Start_pont.setY(second_ball_center.y()-radius);
    End_point.setX(second_ball_center.x() +radius);
    End_point.setY(second_ball_center.y()+radius);

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

    p->drawLine(second_line_start,second_line_end);
    p->drawEllipse(circle_rect);
    p->restore();
}

void Widget::drawThird_ball(QPainter *p)
{
    p->save();
    QRect circle_rect;
    QPoint Start_pont,End_point;
    QPoint lg_start,lg_end;
    Start_pont.setX(third_ball_center.x() -radius);
    Start_pont.setY(third_ball_center.y()-radius);
    End_point.setX(third_ball_center.x() +radius);
    End_point.setY(third_ball_center.y()+radius);

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

    p->drawLine(third_line_start,third_line_end);
    p->drawEllipse(circle_rect);
    p->restore();
}

void Widget::drawfourth_ball(QPainter *p)
{
    p->save();
    QRect circle_rect;
    QPoint Start_pont,End_point;
    QPoint lg_start,lg_end;
    Start_pont.setX(forth_ball_center.x() -radius);
    Start_pont.setY(forth_ball_center.y()-radius);
    End_point.setX(forth_ball_center.x() +radius);
    End_point.setY(forth_ball_center.y()+radius);

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

    p->drawLine(forth_line_start,forth_line_end);
    p->drawEllipse(circle_rect);
    p->restore();
}

void Widget::drawfifth_ball(QPainter *p)
{
    p->save();
    QRect circle_rect;
    QPoint Start_pont,End_point;
    QPoint lg_start,lg_end;
    Start_pont.setX(firth_ball_center.x() -radius);
    Start_pont.setY(firth_ball_center.y()-radius);
    End_point.setX(firth_ball_center.x() +radius);
    End_point.setY(firth_ball_center.y()+radius);

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

    p->drawLine(firth_line_start,firth_line_end);
    p->drawEllipse(circle_rect);
    p->restore();
}


void Widget::newton_cradle_init(void)
{
    //int x_temp,y_temp;
    int left_start = (width() - radius * 2 * (ball_num-1)) / 2;
    int botton_start = height() - down_blank - radius;

    line_len = botton_start - up_blank;
    first_line_start.setX(left_start);
    first_line_start.setY(up_blank);
    first_line_end.setX(left_start);
    first_line_end.setY(botton_start);
    first_ball_center.setX(left_start);
    first_ball_center.setY(botton_start);
    first_ball_original_centor.setX(left_start);
    first_ball_original_centor.setY(botton_start);

    second_line_start.setX(left_start+60);
    second_line_start.setY(up_blank);
    second_line_end.setX(left_start+60);
    second_line_end.setY(botton_start);
    second_ball_center.setX(left_start+60);
    second_ball_center.setY(botton_start);


    third_line_start.setX(left_start+120);
    third_line_start.setY(up_blank);
    third_line_end.setX(left_start+120);
    third_line_end.setY(botton_start);
    third_ball_center.setX(left_start+120);
    third_ball_center.setY(botton_start);

    forth_line_start.setX(left_start+180);
    forth_line_start.setY(up_blank);
    forth_line_end.setX(left_start+180);
    forth_line_end.setY(botton_start);
    forth_ball_center.setX(left_start+180);
    forth_ball_center.setY(botton_start);

    firth_line_start.setX(left_start+240);
    firth_line_start.setY(up_blank);
    firth_line_end.setX(left_start+240);
    firth_line_end.setY(botton_start);
    firth_ball_center.setX(left_start+240);
    firth_ball_center.setY(botton_start);
    firth_ball_original_centor.setX(left_start+240);
    firth_ball_original_centor.setY(botton_start);
}

void Widget::paintEvent(QPaintEvent *)
{

    QPainter p(this);

    drawFirst_ball(&p);
    drawSecond_ball(&p);
    drawThird_ball(&p);
    drawfourth_ball(&p);
    drawfifth_ball(&p);
}


