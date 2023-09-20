#ifndef COMBOBOXCOLORDELEGATE_H
#define COMBOBOXCOLORDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class ComboBoxColorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxColorDelegate(QObject *parent = nullptr);

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

#endif // COMBOBOXCOLORDELEGATE_H
