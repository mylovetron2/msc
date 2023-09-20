#include "curvesetting.h"
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

//class myTableModel;

CurveSetting::CurveSetting(QWidget *parent) : QWidget(parent),
    newButton(new QPushButton("OK"))
{
    ComboBoxColorDelegate* delegateColor = new ComboBoxColorDelegate(this);
    SpinBoxDelegate* delegateWidth=new SpinBoxDelegate(this);
    BooleanCheckBoxDelegate *delegateCheck=new BooleanCheckBoxDelegate(this);

    TableModel *tablemodel =new TableModel();
    tablemodel->setTable("curve");
    //tablemodel->setTable("track_curve");
    //tablemodel->setRelation(2,QSqlRelation("curve","curve_id","name"));
    tablemodel->select();

    tableView=new QTableView();
    tableView->setModel(tablemodel);
    tableView->setItemDelegateForColumn(5,delegateColor);
    tableView->setItemDelegateForColumn(4,delegateWidth);
    //CheckBoxDelegate *delegateCheckBox=new CheckBoxDelegate(tableView);
//tableView->setItemDelegateForColumn(6,delegateCheckBox);
    tableView->setItemDelegateForColumn(6,delegateCheck);

    tableView->setColumnHidden(0,true);
    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    //tableView->setEditTriggers(QAbstractItemView::clicked);

    setWindowTitle("Curve Attribute");
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 0, 0);
    mainLayout->addWidget(newButton,1,0);
    //setCentralWidget(mainLayout);
     setLayout(mainLayout);

}

void CurveSetting::createGUI()
{

}
