#include "widget.h"
#include <QApplication>
#include <QFontDatabase>
#include "QDebug"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    /*
    int index = QFontDatabase::addApplicationFont("LiberationMono-Bold.ttf");
    if (index !=-1)
    {
        QStringList fontList(QFontDatabase::applicationFontFamilies(index));
        if(fontList.count() > 0)
        {
            QFont font(fontList.at(0));
            font.setBold(false);
            a.setFont(font);
            qDebug()<<"Set font success";
        }
    }*/
    return a.exec();
}
