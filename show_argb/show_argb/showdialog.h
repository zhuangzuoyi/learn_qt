#ifndef SHOWDIALOG_H
#define SHOWDIALOG_H

#include <QWidget>

namespace Ui {
class showdialog;
}

class showdialog : public QWidget
{
    Q_OBJECT

public:
    explicit showdialog(QWidget *parent = 0);
    ~showdialog();

private:
    Ui::showdialog *ui;
};

#endif // SHOWDIALOG_H
