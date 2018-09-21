#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *);
    void dial_background(QPainter *p);
    void draw_dial_sendond_background(QPainter *p);
    void draw_dial_background_black(QPainter *p);
    void draw_dial_background_gradual(QPainter *p);
    void draw_dial_speed(QPainter *p);
    void draw_dial_show_01(QPainter *p);
    void draw_dial_show_02(QPainter *p);
    void draw_dial_speed_text(QPainter *p);
    void draw_dial_tick(QPainter *p);
    void draw_dial_tick_02(QPainter *p);
    void draw_dial_scale(QPainter *p);
private slots:
    void timerUpDate();
private:
    int dial_height;
    int dial_widht;
    int Speed;
};

#endif // WIDGET_H
