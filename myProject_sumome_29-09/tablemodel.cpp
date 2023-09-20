#include "tablemodel.h"
#include "QDebug"
#include <QBrush>
#include <QFont>
#include <QColor>
#include <QPainter>
#include <QIcon>

TableModel::TableModel(QObject *parent) : QSqlRelationalTableModel(parent) //QSqlTableModel(parent)
{
    m_indexColorColumn=-1;
}


bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return QSqlTableModel::setData(index, value,role);

}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    QVariant value=QSqlTableModel::data(index, role);

    if(index.isValid()){
        if(role==Qt::DisplayRole){
            QString s=QSqlTableModel::data(index,Qt::DisplayRole).toString();
            return s;
        }
        if(role==Qt::EditRole){
            QString s=QSqlTableModel::data(index,Qt::EditRole).toString();
            return s;
        }
        if(role==Qt::DecorationRole){                               // Color Column
            if (col == m_indexColorColumn)  {
                QString s=index.data(Qt::DisplayRole).toString();
                QColor color;
                color.setNamedColor(s);
                return color;
            }
            if(col==7)       // Delete button
                return QIcon(":/images/images/delete.png");
        }
        /*
        if(col==6){
             if (role == Qt::CheckStateRole){
                      int checked = QSqlTableModel::data(index).toInt();
                      if(checked)
                          return Qt::Checked;
                      else
                          return Qt::Unchecked;

             }

        }*/

    }
    return value;
    //return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    int row = index.row();
    int col = index.column();
    if(col==7)         // Column delete button
        return QSqlTableModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    return QSqlTableModel::flags(index) | Qt::ItemIsEditable;
}

void TableModel::setQuery(const QSqlQuery &query)
{
    QSqlTableModel::setQuery(query);
}

int TableModel::columnCount(const QModelIndex &index) const
{
     return QSqlRelationalTableModel::columnCount() + 1;     // add delete button

}

void TableModel::setColorColumn(int index)
{
     m_indexColorColumn=index;
}


