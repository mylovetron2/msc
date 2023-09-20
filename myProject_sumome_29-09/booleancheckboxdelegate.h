#ifndef BOOLEANCHECKBOXDELEGATE_H
#define BOOLEANCHECKBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QWidget>

class BooleanCheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BooleanCheckBoxDelegate(QObject *parent = nullptr);

signals:
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const override;

     void setEditorData(QWidget *editor, const QModelIndex &index) const override;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const override;

     void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const override;

};

#endif // BOOLEANCHECKBOXDELEGATE_H
