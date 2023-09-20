#ifndef SQLDATAMODEL_H
#define SQLDATAMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QHash>
#include <QRect>

class SqlDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SqlDataModel(QObject *parent = nullptr);

signals:

};

#endif // SQLDATAMODEL_H
