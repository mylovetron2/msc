#include "loaddata.h"
#include "ui_loaddata.h"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <QPushButton>
#include <QDebug>

loaddata::loaddata(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loaddata)
{

    ui->setupUi(this);
    //ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Load");

    QSqlQueryModel *modal=new QSqlQueryModel();
    QString s="SELECT substr(name,6,8),substr(name,15) FROM sqlite_master WHERE type = 'table' and substr(name,0,5) LIKE 'data%' ORDER BY name DESC";
    QSqlQuery qry;
    qry.prepare(s);
    qry.exec();
    modal->setQuery(qry);
    ui->loadDataView->setModel(modal);

    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("DATE"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("TIME"));

    ui->loadDataView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->loadDataView->horizontalHeader()->setHighlightSections(true);
    ui->loadDataView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:darkblue;color:white}");
    ui->loadDataView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->loadDataView->resizeColumnsToContents();
    ui->loadDataView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->loadDataView->setColumnHidden(0,true);

}

loaddata::~loaddata()
{
    delete ui;
}

void loaddata::on_btnAdd_clicked()
{
    //qDebug()<<"btn click";
    QItemSelectionModel *item=ui->loadDataView->selectionModel();
    qint32 row = item->currentIndex().row();
    qint32 col =item->currentIndex().column();
    QAbstractItemModel *model=item->model();
    //model=ui->loadDataView->selectionModel();
    QString s="data_"+model->data(model->index(row,col),Qt::DisplayRole).toString()+"_"+model->data(model->index(row,col+1),Qt::DisplayRole).toString();
    emit loaddata_sig(s);
    //qDebug()<<s;
    this->close();
}

void loaddata::on_btnExit_clicked()
{
    this->close();
}
