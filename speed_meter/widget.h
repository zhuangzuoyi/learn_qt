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
    void paintTitle(QPainter *p);
    void drawLoop(QPainter *p);
    void mousePressEvent(QMouseEvent *e);
    void drawrect(QPainter *p);
    void drawInterLoop(QPainter *p);
    void drawSector(QPainter *p);
    void drawSector_cut(QPainter *p);
    void paintUnit(QPainter *p);
    void paintSpeed(QPainter *p);
private:
    int rect_size;
    int rect_s_x;
    int rect_s_y;
    int loop_size;
    int Speed;
    int flag;
    int red;
public slots:
    void updateValue(void);
};

#endif // WIDGET_H
