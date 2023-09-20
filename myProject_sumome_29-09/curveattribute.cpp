#include "curveattribute.h"
#include "QGridLayout"
#include <QSqlQueryModel>
#include <QAbstractItemModel>
#include "colorlisteditor.h"
#include <QtWidgets>
#include <QAbstractTableModel>
#include "comboboxcolordelegate.h"
#include "checkboxdelegate.h"
#include "spinboxdelegate.h"
#include "tablemodel.h"
#include "mydatamodel.h"
#include "booleancheckboxdelegate.h"
#include <QSqlRecord>
#include <QSqlRelationalDelegate>

const int columnDeleteButton=7;

CurveAttribute::CurveAttribute(int viewID,QWidget *parent) : QWidget(parent),
    newButton(new QPushButton("update")),
    btnInsertRow(new QPushButton("add"))

{
    m_viewId=viewID;

    ComboBoxColorDelegate* delegateColor = new ComboBoxColorDelegate(this);
    SpinBoxDelegate* delegateWidth=new SpinBoxDelegate(this);
    BooleanCheckBoxDelegate *delegateCheck=new BooleanCheckBoxDelegate(this);

    tablemodel =new TableModel();
    tablemodel->setTable("track_curve");
    tablemodel->setHeaderData(columnDeleteButton, Qt::Horizontal, tr(" "));
    tablemodel->setRelation(2,QSqlRelation("curve","curve_id","name"));
    tablemodel->setFilter("trackview_id="+QString::number(viewID));
    tablemodel->setColorColumn(6);
    tablemodel->select();

    tableView=new QTableView();
    tableView->setModel(tablemodel);
    tableView->setItemDelegateForColumn(6,delegateColor);
    tableView->setItemDelegateForColumn(5,delegateWidth);
    tableView->setItemDelegate(new QSqlRelationalDelegate(this));
    //tableView->setColumnWidth(columnDeleteButton,5);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(columnDeleteButton,QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setHighlightSections(true);
    tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:darkblue;color:white}");
    //CheckBoxDelegate *delegateCheckBox=new CheckBoxDelegate(tableView);
    //tableView->setItemDelegateForColumn(6,delegateCheckBox);
    //tableView->setItemDelegateForColumn(6,delegateCheck);

    tableView->setColumnHidden(0,true);
    tableView->setColumnHidden(1,true);
    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);

    setWindowTitle("Curve Attribute");
    setWindowIcon(QIcon(":/images/images/curve_attribute.png"));
    QVBoxLayout *vLayout= new QVBoxLayout();
    QHBoxLayout *hLayout= new QHBoxLayout();

    vLayout->addWidget(tableView);
    hLayout->addStretch();
    hLayout->addWidget(newButton);
    hLayout->addWidget(btnInsertRow);

    vLayout->addLayout(hLayout);
    setLayout(vLayout);
    this->resize(600, 500);

    connect(this->btnInsertRow,&QPushButton::clicked,this,&CurveAttribute::insertRow);
    connect(tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClick(const QModelIndex &)));

}

void CurveAttribute::insertRow()
{
    int rowcount=tablemodel->rowCount();

    tableView->scrollTo(tablemodel->index(rowcount,2));
    tableView->setCurrentIndex(tablemodel->index(rowcount,2));
    tableView->setFocus();

    tablemodel->insertRow(tablemodel->rowCount());
    qDebug()<<"Add curve trackview_id" <<tablemodel->setData(tablemodel->index(rowcount,1),m_viewId,Qt::EditRole);
    qDebug()<<"Add curve curve_id" <<tablemodel->setData(tablemodel->index(rowcount,2),1,Qt::EditRole);
    qDebug()<<"Add curve color" <<tablemodel->setData(tablemodel->index(rowcount,6),"black",Qt::EditRole);
    tablemodel->submitAll();
    tableView->edit(tablemodel->index(rowcount,2));
    tablemodel->setEditStrategy(QSqlTableModel::EditStrategy::OnRowChange);


}


void CurveAttribute::deleteRow()                //ko dung nua, de tham khao
{
    QModelIndexList selection = tableView->selectionModel()->selectedRows();
    if(selection.count()>0){
        for(int i=0; i< selection.count(); i++)
        {
            QModelIndex index = selection.at(i);
            qDebug()<<tablemodel->removeRow(index.row());
         }
        tablemodel->submitAll();
        tablemodel->select();
    }

}

void CurveAttribute::onTableClick(const QModelIndex &index)
{
    if (index.isValid()) {
        if(index.column()==columnDeleteButton)            //Delete button
               qDebug()<<tablemodel->removeRow(index.row());
               tablemodel->submitAll();
               tablemodel->select();
       }
}

