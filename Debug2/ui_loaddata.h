/********************************************************************************
** Form generated from reading UI file 'loaddata.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADDATA_H
#define UI_LOADDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_loaddata
{
public:
    QTableView *loadDataView;
    QSplitter *splitter;
    QPushButton *btnAdd;
    QPushButton *btnExit;

    void setupUi(QDialog *loaddata)
    {
        if (loaddata->objectName().isEmpty())
            loaddata->setObjectName(QString::fromUtf8("loaddata"));
        loaddata->resize(403, 441);
        loadDataView = new QTableView(loaddata);
        loadDataView->setObjectName(QString::fromUtf8("loadDataView"));
        loadDataView->setGeometry(QRect(20, 20, 361, 341));
        loadDataView->setSelectionMode(QAbstractItemView::SingleSelection);
        loadDataView->setSortingEnabled(false);
        loadDataView->verticalHeader()->setVisible(false);
        loadDataView->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        splitter = new QSplitter(loaddata);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(110, 380, 186, 28));
        splitter->setOrientation(Qt::Horizontal);
        btnAdd = new QPushButton(splitter);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        splitter->addWidget(btnAdd);
        btnExit = new QPushButton(splitter);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));
        splitter->addWidget(btnExit);

        retranslateUi(loaddata);

        QMetaObject::connectSlotsByName(loaddata);
    } // setupUi

    void retranslateUi(QDialog *loaddata)
    {
        loaddata->setWindowTitle(QCoreApplication::translate("loaddata", "Load data", nullptr));
        btnAdd->setText(QCoreApplication::translate("loaddata", "Add", nullptr));
        btnExit->setText(QCoreApplication::translate("loaddata", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loaddata: public Ui_loaddata {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADDATA_H
