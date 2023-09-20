#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

//#include <QObject>
#include <QAbstractTableModel>

class myTableModel : public QAbstractTableModel
{
     Q_OBJECT
public:
    explicit  myTableModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // MYTABLEMODEL_H
