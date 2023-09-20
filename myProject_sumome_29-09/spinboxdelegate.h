#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class SpinBoxDelegate :public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SpinBoxDelegate(QObject *parent = nullptr);

signals:
public:
       QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

        void setEditorData(QWidget *editor, const QModelIndex &index) const override;
        void setModelData(QWidget *editor, QAbstractItemModel *model,
                          const QModelIndex &index) const override;

        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;

};

#endif // SPINBOXDELEGATE_H
