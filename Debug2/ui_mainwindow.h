/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSetting_connect;
    QAction *actionDevice_connect;
    QAction *actionDisconnect;
    QAction *actionExit;
    QAction *actionCurve;
    QAction *actionSave_layout;
    QAction *actionLoad_layout;
    QAction *actionExit_2;
    QAction *actionLoad_data;
    QAction *actionExport_file;
    QAction *actionParameter;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuCurve;
    QMenu *menuSetting;
    QMenu *menuLogging;
    QMenu *menuFile;
    QMenu *menuData;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(592, 327);
        MainWindow->setAutoFillBackground(false);
        actionSetting_connect = new QAction(MainWindow);
        actionSetting_connect->setObjectName(QString::fromUtf8("actionSetting_connect"));
        actionSetting_connect->setCheckable(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetting_connect->setIcon(icon);
        actionDevice_connect = new QAction(MainWindow);
        actionDevice_connect->setObjectName(QString::fromUtf8("actionDevice_connect"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDevice_connect->setIcon(icon1);
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionCurve = new QAction(MainWindow);
        actionCurve->setObjectName(QString::fromUtf8("actionCurve"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/images/curve_attribute.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCurve->setIcon(icon4);
        actionSave_layout = new QAction(MainWindow);
        actionSave_layout->setObjectName(QString::fromUtf8("actionSave_layout"));
        actionLoad_layout = new QAction(MainWindow);
        actionLoad_layout->setObjectName(QString::fromUtf8("actionLoad_layout"));
        actionExit_2 = new QAction(MainWindow);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        actionLoad_data = new QAction(MainWindow);
        actionLoad_data->setObjectName(QString::fromUtf8("actionLoad_data"));
        actionExport_file = new QAction(MainWindow);
        actionExport_file->setObjectName(QString::fromUtf8("actionExport_file"));
        actionParameter = new QAction(MainWindow);
        actionParameter->setObjectName(QString::fromUtf8("actionParameter"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 592, 26));
        menuCurve = new QMenu(menubar);
        menuCurve->setObjectName(QString::fromUtf8("menuCurve"));
        menuSetting = new QMenu(menubar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        menuLogging = new QMenu(menubar);
        menuLogging->setObjectName(QString::fromUtf8("menuLogging"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuData = new QMenu(menubar);
        menuData->setObjectName(QString::fromUtf8("menuData"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuCurve->menuAction());
        menubar->addAction(menuLogging->menuAction());
        menubar->addAction(menuData->menuAction());
        menubar->addAction(menuSetting->menuAction());
        menuCurve->addAction(actionDevice_connect);
        menuCurve->addAction(actionDisconnect);
        menuCurve->addAction(actionExit);
        menuSetting->addAction(actionSetting_connect);
        menuSetting->addAction(actionParameter);
        menuLogging->addAction(actionCurve);
        menuFile->addAction(actionSave_layout);
        menuFile->addAction(actionLoad_layout);
        menuFile->addSeparator();
        menuFile->addAction(actionExit_2);
        menuData->addAction(actionLoad_data);
        menuData->addAction(actionExport_file);
        toolBar->addAction(actionDevice_connect);
        toolBar->addAction(actionDisconnect);
        toolBar->addAction(actionSetting_connect);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Logging", nullptr));
        actionSetting_connect->setText(QCoreApplication::translate("MainWindow", "Connect setting", nullptr));
        actionDevice_connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionCurve->setText(QCoreApplication::translate("MainWindow", "Curve Attribute", nullptr));
        actionSave_layout->setText(QCoreApplication::translate("MainWindow", "Save layout", nullptr));
        actionLoad_layout->setText(QCoreApplication::translate("MainWindow", "Load layout", nullptr));
        actionExit_2->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionLoad_data->setText(QCoreApplication::translate("MainWindow", "Load data", nullptr));
        actionExport_file->setText(QCoreApplication::translate("MainWindow", "Export file", nullptr));
        actionParameter->setText(QCoreApplication::translate("MainWindow", "Parameter", nullptr));
        menuCurve->setTitle(QCoreApplication::translate("MainWindow", "Device", nullptr));
        menuSetting->setTitle(QCoreApplication::translate("MainWindow", "Setting", nullptr));
        menuLogging->setTitle(QCoreApplication::translate("MainWindow", "Logging", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuData->setTitle(QCoreApplication::translate("MainWindow", "Data", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
