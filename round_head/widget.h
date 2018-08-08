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
    void drawCover(QPainter *p);
    void drawpic(QPainter *p);
};

#endif // WIDGET_H
