#include "mainwindow.h"
#include "tablewidget.h"
#include "sqlwidget.h"
#include "connection.h"
#include <stdlib.h>
#include <QApplication>
#include "trackview.h"
#include "curvesetting.h"
#include "QLabel"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection())
        return EXIT_FAILURE;
    QCoreApplication::setOrganizationName("MySoft");
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Star Runner");

    MainWindow  w;
    //TableWidget w;
    //QRect rect(0, 0, 640, 320);
    //CurveSetting w;
    //w.setGeometry(rect);
    //w.setCentralWidget(new QLabel("test"));


    //QPalette p =w.palette();
    //p.setColor(w.backgroundRole(),Qt::red);
    //w.setPalette(p);

    w.show();
    return a.exec();
}
