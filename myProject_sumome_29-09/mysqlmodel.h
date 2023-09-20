#ifndef MYDATATABLE_H
#define MYDATATABLE_H

#include <QObject>
#include <QAbstractTableModel>
#include <QHash>
#include <QRect>

class myDataTable : public QAbstractTableModel
{
    Q_OBJECT
private:

    QList<QVector<qreal> * > m_data;
    QHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;

public:
    explicit myDataTable(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
signals:

};




#endif // MYDATATABLE_H
