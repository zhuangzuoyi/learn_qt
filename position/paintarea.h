#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    enum Shape{
        Line,
        Rectangle,
        RoundRect,
        Ellipse,
        Polygon,
        Polyline,
        Points,
        Arc,
        Path,
        Text,
        Pinmap
    };
    explicit PaintArea(QWidget *parent=0);
    void setShape(Shape);
    void setPen(QPen);
    void setBrush(QBrush);
    void setFillRule(Qt::FillRule);
    void paintEvent(QPaintEvent *);

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;
public:
    explicit PaintArea(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PAINTAREA_H
