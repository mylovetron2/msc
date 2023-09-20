#include "mytablemodel.h"




myTableModel::myTableModel(QObject *parent)
 : QAbstractTableModel(parent)
{

}

int myTableModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

int myTableModel::rowCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant myTableModel::data(const QModelIndex &index, int role) const
{
     return QVariant();
}

