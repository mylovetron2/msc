#include "sqlwidget.h"
#include "tablewidget.h"
#include "QTableView"
#include "mydatatable.h"
#include <QHeaderView>
#include <QtWidgets/QGridLayout>

sqlwidget::sqlwidget(QWidget *parent) : QWidget(parent)
{
    myDataTable *model = new myDataTable;

    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // create main layout
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(tableView, 1, 0);
        //mainLayout->addWidget(chartView, 1, 1);
        //mainLayout->setColumnStretch(1, 1);
        //mainLayout->setColumnStretch(0, 0);
        setLayout(mainLayout);
}
