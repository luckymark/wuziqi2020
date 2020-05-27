/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *titleLabel;
    QLabel *timeLabel;
    QLabel *stepLabel;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Bradley Hand ITC"));
        font.setPointSize(12);
        Widget->setFont(font);
        titleLabel = new QLabel(Widget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(100, 50, 461, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(16);
        titleLabel->setFont(font1);
        titleLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        titleLabel->setMargin(5);
        timeLabel = new QLabel(Widget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setGeometry(QRect(680, 160, 121, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Lucida Bright"));
        font2.setPointSize(12);
        timeLabel->setFont(font2);
        stepLabel = new QLabel(Widget);
        stepLabel->setObjectName(QString::fromUtf8("stepLabel"));
        stepLabel->setGeometry(QRect(680, 400, 111, 31));
        stepLabel->setFont(font2);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        titleLabel->setText(QCoreApplication::translate("Widget", "Welcome to GoBang for Homework", nullptr));
        timeLabel->setText(QCoreApplication::translate("Widget", "Time: 0", nullptr));
        stepLabel->setText(QCoreApplication::translate("Widget", "Steps: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
