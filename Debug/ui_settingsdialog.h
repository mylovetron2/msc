/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyButton;
    QGroupBox *selectBox;
    QGridLayout *gridLayout;
    QLabel *vidLabel;
    QLabel *descriptionLabel;
    QLabel *baudRateLabel;
    QLabel *pidLabel;
    QComboBox *serialPortInfoListBox;
    QLabel *serialNumberLabel;
    QLabel *locationLabel;
    QLabel *manufacturerLabel;
    QComboBox *baudRateBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(281, 272);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsDialog->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(SettingsDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(96, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        applyButton = new QPushButton(SettingsDialog);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));

        horizontalLayout->addWidget(applyButton);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 2);

        selectBox = new QGroupBox(SettingsDialog);
        selectBox->setObjectName(QString::fromUtf8("selectBox"));
        gridLayout = new QGridLayout(selectBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vidLabel = new QLabel(selectBox);
        vidLabel->setObjectName(QString::fromUtf8("vidLabel"));

        gridLayout->addWidget(vidLabel, 7, 0, 1, 1);

        descriptionLabel = new QLabel(selectBox);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));

        gridLayout->addWidget(descriptionLabel, 3, 0, 1, 1);

        baudRateLabel = new QLabel(selectBox);
        baudRateLabel->setObjectName(QString::fromUtf8("baudRateLabel"));

        gridLayout->addWidget(baudRateLabel, 1, 0, 1, 1);

        pidLabel = new QLabel(selectBox);
        pidLabel->setObjectName(QString::fromUtf8("pidLabel"));

        gridLayout->addWidget(pidLabel, 8, 0, 1, 1);

        serialPortInfoListBox = new QComboBox(selectBox);
        serialPortInfoListBox->setObjectName(QString::fromUtf8("serialPortInfoListBox"));

        gridLayout->addWidget(serialPortInfoListBox, 0, 0, 1, 1);

        serialNumberLabel = new QLabel(selectBox);
        serialNumberLabel->setObjectName(QString::fromUtf8("serialNumberLabel"));

        gridLayout->addWidget(serialNumberLabel, 5, 0, 1, 1);

        locationLabel = new QLabel(selectBox);
        locationLabel->setObjectName(QString::fromUtf8("locationLabel"));

        gridLayout->addWidget(locationLabel, 6, 0, 1, 1);

        manufacturerLabel = new QLabel(selectBox);
        manufacturerLabel->setObjectName(QString::fromUtf8("manufacturerLabel"));

        gridLayout->addWidget(manufacturerLabel, 4, 0, 1, 1);

        baudRateBox = new QComboBox(selectBox);
        baudRateBox->setObjectName(QString::fromUtf8("baudRateBox"));

        gridLayout->addWidget(baudRateBox, 2, 0, 1, 1);


        gridLayout_3->addWidget(selectBox, 0, 0, 1, 2);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Settings", nullptr));
        applyButton->setText(QCoreApplication::translate("SettingsDialog", "Apply", nullptr));
        selectBox->setTitle(QCoreApplication::translate("SettingsDialog", "Select Serial Port", nullptr));
        vidLabel->setText(QCoreApplication::translate("SettingsDialog", "Vendor ID:", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("SettingsDialog", "Description:", nullptr));
        baudRateLabel->setText(QCoreApplication::translate("SettingsDialog", "BaudRate:", nullptr));
        pidLabel->setText(QCoreApplication::translate("SettingsDialog", "Product ID:", nullptr));
        serialNumberLabel->setText(QCoreApplication::translate("SettingsDialog", "Serial number:", nullptr));
        locationLabel->setText(QCoreApplication::translate("SettingsDialog", "Location:", nullptr));
        manufacturerLabel->setText(QCoreApplication::translate("SettingsDialog", "Manufacturer:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
