#include "mydatatable.h"
#include <QtCore/QRandomGenerator>
#include <QColor>

myDataTable::myDataTable(QObject *parent) :QAbstractTableModel(parent)
{
       m_columnCount = 4;
       m_rowCount = 15;

       // m_data
       for (int i = 0; i < m_rowCount; i++) {
           QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
           for (int k = 0; k < dataVec->size(); k++) {
               if (k % 2 == 0)
                   dataVec->replace(k, i * 50 + QRandomGenerator::global()->bounded(20));
               else
                   dataVec->replace(k, QRandomGenerator::global()->bounded(100));
           }
           m_data.append(dataVec);
       }
       QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
       for (int k = 0; k < dataVec->size(); k++)
           dataVec->replace(k, 50);
       m_data.append(dataVec);
}

int myDataTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int myDataTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

bool myDataTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
            m_data[index.row()]->replace(index.column(), value.toDouble());
            emit dataChanged(index, index);
            return true;
        }
        return false;
}

QVariant myDataTable::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
            return m_data[index.row()]->at(index.column());
        } else if (role == Qt::EditRole) {
            return m_data[index.row()]->at(index.column());
        } else if (role == Qt::BackgroundRole) {
            for (const QRect &rect : m_mapping) {
                if (rect.contains(index.column(), index.row()))
                    return QColor(m_mapping.key(rect));
            }
            // cell not mapped return white color
            return QColor(Qt::white);
        }
        return QVariant();
}
