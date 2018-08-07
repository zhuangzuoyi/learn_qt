#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QTimer"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    //void drawCircle(QPainter *p);
    //void drawline(QPainter *p);
    void newton_cradle_init(void);

    void drawFirst_ball(QPainter *p);
    void drawSecond_ball(QPainter *p);
    void drawThird_ball(QPainter *p);
    void drawfourth_ball(QPainter *p);
    void drawfifth_ball(QPainter *p);
    void mouseReleaseEvent(QMouseEvent *);
private:
     QPoint Circle_point;
     int canvas_width;
     int canvas_height;
     int ball_num;
     int radius;
     int up_blank;
     int down_blank;
     int moving_ball;
     QPoint moving_point_old;
     QPoint first_ball_center;
     QPoint first_line_start;
     QPoint first_line_end;
     QPoint first_ball_original_centor;

     QPoint second_ball_center;
     QPoint second_line_start;
     QPoint second_line_end;

     QPoint third_ball_center;
     QPoint third_line_start;
     QPoint third_line_end;

     QPoint forth_ball_center;
     QPoint forth_line_start;
     QPoint forth_line_end;

     QPoint firth_ball_center;
     QPoint firth_line_start;
     QPoint firth_line_end;
     QPoint firth_ball_original_centor;

     int line_len;
     QTimer *timer;
     int timer_interval;
private  slots:
    void timeout();
};

#endif // WIDGET_H
