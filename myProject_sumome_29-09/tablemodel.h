#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

class TableModel : public  QSqlRelationalTableModel //QSqlTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);
    bool setData( const QModelIndex &index, const QVariant &value, int role );
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void setQuery(const QSqlQuery &query);
    int	columnCount(const QModelIndex &index = QModelIndex()) const override;


signals:
private:
    int m_indexColorColumn;
public:
    void setColorColumn(int index);

};

#endif // TABLEMODEL_H
