/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *com_port;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *baudrate;
    QPushButton *OpenCom;
    QComboBox *line_count;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *container;
    QLabel *label_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(856, 630);
        horizontalLayout_4 = new QHBoxLayout(Widget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        com_port = new QComboBox(Widget);
        com_port->setObjectName(QString::fromUtf8("com_port"));

        horizontalLayout->addWidget(com_port);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        baudrate = new QComboBox(Widget);
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->addItem(QString());
        baudrate->setObjectName(QString::fromUtf8("baudrate"));

        horizontalLayout_2->addWidget(baudrate);


        verticalLayout->addLayout(horizontalLayout_2);

        OpenCom = new QPushButton(Widget);
        OpenCom->setObjectName(QString::fromUtf8("OpenCom"));

        verticalLayout->addWidget(OpenCom);

        line_count = new QComboBox(Widget);
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->addItem(QString());
        line_count->setObjectName(QString::fromUtf8("line_count"));

        verticalLayout->addWidget(line_count);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 458, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_2);

        container = new QVBoxLayout();
        container->setSpacing(6);
        container->setObjectName(QString::fromUtf8("container"));

        horizontalLayout_3->addLayout(container);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 20);

        verticalLayout_4->addLayout(horizontalLayout_3);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_4->addWidget(label_3);


        horizontalLayout_4->addLayout(verticalLayout_4);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "loging", nullptr));
        label->setText(QApplication::translate("Widget", "\344\270\262\345\217\243", nullptr));
        label_2->setText(QApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207", nullptr));
        baudrate->setItemText(0, QApplication::translate("Widget", "9600", nullptr));
        baudrate->setItemText(1, QApplication::translate("Widget", "14400", nullptr));
        baudrate->setItemText(2, QApplication::translate("Widget", "19200", nullptr));
        baudrate->setItemText(3, QApplication::translate("Widget", "28800", nullptr));
        baudrate->setItemText(4, QApplication::translate("Widget", "38400", nullptr));
        baudrate->setItemText(5, QApplication::translate("Widget", "57600", nullptr));
        baudrate->setItemText(6, QApplication::translate("Widget", "115200", nullptr));
        baudrate->setItemText(7, QApplication::translate("Widget", "230400", nullptr));
        baudrate->setItemText(8, QApplication::translate("Widget", "460800", nullptr));

        OpenCom->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        line_count->setItemText(0, QApplication::translate("Widget", "0", nullptr));
        line_count->setItemText(1, QApplication::translate("Widget", "1", nullptr));
        line_count->setItemText(2, QApplication::translate("Widget", "2", nullptr));
        line_count->setItemText(3, QApplication::translate("Widget", "3", nullptr));
        line_count->setItemText(4, QApplication::translate("Widget", "4", nullptr));
        line_count->setItemText(5, QApplication::translate("Widget", "5", nullptr));
        line_count->setItemText(6, QApplication::translate("Widget", "6", nullptr));
        line_count->setItemText(7, QApplication::translate("Widget", "7", nullptr));
        line_count->setItemText(8, QApplication::translate("Widget", "8", nullptr));
        line_count->setItemText(9, QApplication::translate("Widget", "9", nullptr));
        line_count->setItemText(10, QApplication::translate("Widget", "10", nullptr));

        label_3->setText(QApplication::translate("Widget", "status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
