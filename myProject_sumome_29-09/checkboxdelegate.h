#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CheckBoxDelegate(QObject *parent = nullptr);

signals:
public:
    void paint(QPainter * painter, const QStyleOptionViewItem & option,
            const QModelIndex & index ) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index);
};

#endif // CHECKBOXDELEGATE_H
