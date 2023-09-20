#ifndef CURVEATTRIBUTE_H
#define CURVEATTRIBUTE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <tablemodel.h>


class CurveAttribute : public QWidget
{
    Q_OBJECT
public:
    explicit CurveAttribute(int viewID,QWidget *parent = nullptr);

signals:

private:
    //QSqlTableModel *model;
    QTableView *tableView;
    int m_viewId;

public:
    QPushButton *newButton;
    QPushButton *btnUpdate;
    QPushButton *btnInsertRow;
    TableModel *tablemodel;

    void insertRow();
    void deleteRow(); //tham khao

public slots:
    void onTableClick(const QModelIndex &index);

};

#endif // CURVEATTRIBUTE_H
