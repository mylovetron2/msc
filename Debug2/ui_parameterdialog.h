/********************************************************************************
** Form generated from reading UI file 'parameterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERDIALOG_H
#define UI_PARAMETERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_ParameterDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ParameterDialog)
    {
        if (ParameterDialog->objectName().isEmpty())
            ParameterDialog->setObjectName(QString::fromUtf8("ParameterDialog"));
        ParameterDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ParameterDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(ParameterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ParameterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ParameterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ParameterDialog);
    } // setupUi

    void retranslateUi(QDialog *ParameterDialog)
    {
        ParameterDialog->setWindowTitle(QCoreApplication::translate("ParameterDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParameterDialog: public Ui_ParameterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERDIALOG_H
