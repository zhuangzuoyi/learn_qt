#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QUdpSocket"
//#include "qnetwork.h"
#include "QTcpSocket"
#include "QTcpServer"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_openbtn_clicked();


    void newClientConnect(void);

    void readMessage();

    void disConnect();

private:
    Ui::Widget *ui;
    QMovie *movie;
    int current_frame_index;
//    QUdpSocket  *updsocket;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    int img_row,img_list;
    int is_img_load;
    int process_step;

    void send_process(QByteArray dat,int len);
    void send_process(void);
    void load_gif();
    void log(QString msg);
private slots:
    void framechange(void);
};

#endif // WIDGET_H
