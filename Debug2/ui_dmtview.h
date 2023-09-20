/********************************************************************************
** Form generated from reading UI file 'dmtview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DMTVIEW_H
#define UI_DMTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DMTView
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdDepth;
    QLCDNumber *lcdSpeed;
    QLCDNumber *lcdVoltAc;
    QLCDNumber *lcdAmpe;
    QLCDNumber *lcdTension;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *lbl;
    QLabel *label_4;

    void setupUi(QWidget *DMTView)
    {
        if (DMTView->objectName().isEmpty())
            DMTView->setObjectName(QString::fromUtf8("DMTView"));
        DMTView->resize(229, 178);
        layoutWidget = new QWidget(DMTView);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 10, 101, 161));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lcdDepth = new QLCDNumber(layoutWidget);
        lcdDepth->setObjectName(QString::fromUtf8("lcdDepth"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        lcdDepth->setFont(font);
        lcdDepth->setFrameShape(QFrame::Box);
        lcdDepth->setSmallDecimalPoint(false);
        lcdDepth->setDigitCount(3);
        lcdDepth->setSegmentStyle(QLCDNumber::Flat);
        lcdDepth->setProperty("value", QVariant(0.000000000000000));
        lcdDepth->setProperty("intValue", QVariant(0));

        verticalLayout->addWidget(lcdDepth);

        lcdSpeed = new QLCDNumber(layoutWidget);
        lcdSpeed->setObjectName(QString::fromUtf8("lcdSpeed"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        lcdSpeed->setFont(font1);
        lcdSpeed->setSmallDecimalPoint(true);
        lcdSpeed->setDigitCount(3);
        lcdSpeed->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout->addWidget(lcdSpeed);

        lcdVoltAc = new QLCDNumber(layoutWidget);
        lcdVoltAc->setObjectName(QString::fromUtf8("lcdVoltAc"));
        lcdVoltAc->setFont(font1);
        lcdVoltAc->setDigitCount(3);
        lcdVoltAc->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout->addWidget(lcdVoltAc);

        lcdAmpe = new QLCDNumber(layoutWidget);
        lcdAmpe->setObjectName(QString::fromUtf8("lcdAmpe"));
        lcdAmpe->setFont(font1);
        lcdAmpe->setAutoFillBackground(false);
        lcdAmpe->setStyleSheet(QString::fromUtf8(""));
        lcdAmpe->setDigitCount(3);
        lcdAmpe->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout->addWidget(lcdAmpe);

        lcdTension = new QLCDNumber(layoutWidget);
        lcdTension->setObjectName(QString::fromUtf8("lcdTension"));
        lcdTension->setFont(font1);
        lcdTension->setSmallDecimalPoint(true);
        lcdTension->setDigitCount(3);
        lcdTension->setSegmentStyle(QLCDNumber::Flat);
        lcdTension->setProperty("value", QVariant(0.000000000000000));

        verticalLayout->addWidget(lcdTension);

        layoutWidget1 = new QWidget(DMTView);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 92, 161));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Rockwell Extra Bold"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        label->setTextFormat(Qt::PlainText);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font2);
        label_2->setTextFormat(Qt::PlainText);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);
        label_3->setTextFormat(Qt::PlainText);

        verticalLayout_2->addWidget(label_3);

        lbl = new QLabel(layoutWidget1);
        lbl->setObjectName(QString::fromUtf8("lbl"));
        lbl->setFont(font2);
        lbl->setTextFormat(Qt::PlainText);

        verticalLayout_2->addWidget(lbl);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);
        label_4->setTextFormat(Qt::PlainText);

        verticalLayout_2->addWidget(label_4);


        retranslateUi(DMTView);

        QMetaObject::connectSlotsByName(DMTView);
    } // setupUi

    void retranslateUi(QWidget *DMTView)
    {
        DMTView->setWindowTitle(QCoreApplication::translate("DMTView", "DMT", nullptr));
        label->setText(QCoreApplication::translate("DMTView", "DEPTH", nullptr));
        label_2->setText(QCoreApplication::translate("DMTView", "SPEED", nullptr));
        label_3->setText(QCoreApplication::translate("DMTView", "VOLT AC", nullptr));
        lbl->setText(QCoreApplication::translate("DMTView", "AMPE", nullptr));
        label_4->setText(QCoreApplication::translate("DMTView", "TENSION", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DMTView: public Ui_DMTView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DMTVIEW_H
