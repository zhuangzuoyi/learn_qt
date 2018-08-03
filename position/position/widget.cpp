#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Geometry"));
    xLabel = new QLabel(tr("x():"));
    xValueLabel = new QLabel();
    yLabel = new QLabel(tr("y():"));
    yValueLabel = new QLabel();
    FrmLabel = new QLabel(tr("Frame:"));
    FrmValueLabel = new QLabel;
    posLabel = new QLabel(tr("pos():"));
    posValueLabel = new QLabel;
    geoLabel = new QLabel(tr("geometry():"));
    geoValueLabel = new QLabel;
    widthLabel = new QLabel(tr("width():"));
    widthValueLabel = new QLabel;
    heightLabel = new QLabel(tr("height():"));
    heightValueLabel = new QLabel;
    rectLabel = new QLabel(tr("rect():"));
    rectValueLabel = new QLabel();
    sizeLabel = new QLabel (tr("size():"));
    sizeValueLabel = new QLabel;

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(xLabel,0,0);
    mainLayout->addWidget(xValueLabel,0,1);
    mainLayout->addWidget(yLabel,1,0);
    mainLayout->addWidget(yValueLabel,1,1);
    mainLayout->addWidget(FrmLabel,2,0);
    mainLayout->addWidget(FrmValueLabel,2,1);
    mainLayout->addWidget(posLabel,3,0);
    mainLayout->addWidget(posValueLabel,3,1);
    mainLayout->addWidget(geoLabel,4,0);
    mainLayout->addWidget(geoValueLabel,4,1);
    mainLayout->addWidget(widthLabel,5,0);
    mainLayout->addWidget(widthValueLabel,5,1);
    mainLayout->addWidget(heightLabel,6,0);
    mainLayout->addWidget(heightValueLabel,6,1);
    mainLayout->addWidget(rectLabel,7,0);
    mainLayout->addWidget(rectValueLabel,7,1);
    mainLayout->addWidget(sizeLabel,8,0);
    mainLayout->addWidget(sizeValueLabel,8,1);

    updateLabel();
}

Widget::~Widget()
{

}

void Widget::updateLabel()
{
    QString xStr;
    xValueLabel->setText(xStr.setNum(x()));

    QString yStr;
    yValueLabel->setText(yStr.setNum(y()));

    QString frameStr;
    QString tempStr1,tempStr2,tempStr3,tempStr4;
    frameStr = tempStr1.setNum(frameGeometry().x()) + "," +
            tempStr2.setNum(frameGeometry().y()) + "," +
            tempStr3.setNum(frameGeometry().width()) + "," +
            tempStr4.setNum(frameGeometry().height());
   FrmValueLabel ->setText(frameStr);

    QString positionStr;
    QString tempstr11,tempstr12;
    positionStr = tempstr11.setNum(pos().x()) + "," +
            tempstr12.setNum(pos().y());
    posValueLabel ->setText(positionStr);

    QString geoStr;
    QString tempStr21,tempStr22,tempStr23,tempStr24;
    geoStr = tempStr21.setNum(geometry().x()) + "," +
            tempStr22.setNum(geometry().y()) + "," +
            tempStr23.setNum(geometry().width()) + "," +
            tempStr24.setNum(geometry().height()) + "," ;
    geoValueLabel->setText(geoStr);

    QString wStr,hStr;
    widthValueLabel->setText(wStr.setNum(width()));
    heightValueLabel->setText(hStr.setNum(height()));


    QString rectStr;
    QString tempStr40,tempStr41,tempStr42,tempStr43;
    rectStr = tempStr40.setNum(rect().x()) + "," +
              tempStr41.setNum(rect().y()) + "," +
              tempStr42.setNum(rect().width()) + "," +
              tempStr43.setNum(rect().height());
    rectValueLabel->setText(rectStr);

    QString sizeStr;
    QString tempStr50,tempStr51;
    sizeStr = tempStr50.setNum(size().width()) + "," +
              tempStr51.setNum(size().height());
    sizeValueLabel->setText(sizeStr);
}

void Widget::moveEvent(QMoveEvent *)
{
    updateLabel();
}
void Widget::resizeEvent(QResizeEvent *)
{
    updateLabel();
}
