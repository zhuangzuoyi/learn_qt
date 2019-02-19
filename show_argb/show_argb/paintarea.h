#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
//    enum Shape{Line,Rectangle,RoundRect,Ellipse,Polygon,Polyline,Points,Arc,Path,Text,Pixmap};
    explicit PaintArea(QWidget *parent = 0);

    void paintEvent(QPaintEvent *);
    void setFilePath(QString file);
    void setPixelSize(int size);
    void setHeight(int height);
    void setWidth(int width);
    void setImgData(QByteArray img_dat);

signals:

public slots:
private:
//    Shape shape;
    QPen pen;
    QBrush brush;
    int img_width;
    int img_height;
    int pixel_size;
    QString file_path;
    QByteArray img_data;
//    Qt::FillRule fillRule;

};

#endif // PAINTAREA_H
