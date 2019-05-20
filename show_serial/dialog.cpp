#include "dialog.h"
#include "ui_dialog.h"
#include "QtSerialPort/QSerialPortInfo"
#include "QAction"
#include "QMenu"
#include "QKeyEvent"
#include "QMessageBox"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


    QIcon icon = QIcon(":/serial.jpg");

    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);

    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(icon);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Dialog::iconActivated);
    trayIcon->show();
    update_serial_info();
}

void Dialog::update_serial_info(void)
{
    this->ui->msg->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QString menu_temp = info.portName() + ":" + info.description();
        this->ui->msg->append(menu_temp);
    }
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_F5)
    {
        update_serial_info();
    }
}


void Dialog::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}


void Dialog::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
    case QSystemTrayIcon::MiddleClick:
        show();
        break;
    default:
        ;
    }
}
