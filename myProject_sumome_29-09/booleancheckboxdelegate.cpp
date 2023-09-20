#include "booleancheckboxdelegate.h"
#include <QCheckBox>
#include <QApplication>
#include <QPainter>

BooleanCheckBoxDelegate::BooleanCheckBoxDelegate(QObject *parent)
{

}

void BooleanCheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool data = index.model()->data(index, Qt::DisplayRole).toBool();

    //create CheckBox style
    QStyleOptionButton checkboxstyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);

    //center
    checkboxstyle.rect = option.rect;
    checkboxstyle.rect.setLeft(option.rect.x() +
                               option.rect.width()/2 - checkbox_rect.width()/2);
    //checked or not checked
    if(data)
        checkboxstyle.state = QStyle::State_On|QStyle::State_Enabled;
    else
        checkboxstyle.state = QStyle::State_Off|QStyle::State_Enabled;

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setPen(Qt::red);
        painter->setBrush(option.palette.highlightedText());
    }

    //done! we can draw!
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxstyle, painter);
}

QWidget *BooleanCheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QCheckBox *editor = new QCheckBox(parent);
    return editor;
}

void BooleanCheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //set if checked or not
    QCheckBox *cb = qobject_cast<QCheckBox *>(editor);
    cb->setChecked(index.data().toBool());
}

void BooleanCheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox *cb = static_cast<QCheckBox *>(editor);
    int value = (cb->checkState()==Qt::Checked)?1:0;
    model->setData(index, value, Qt::EditRole);
}

void BooleanCheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QStyleOptionButton checkboxstyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);

    //center
    checkboxstyle.rect = option.rect;
    checkboxstyle.rect.setLeft(option.rect.x() +
                               option.rect.width()/2 - checkbox_rect.width()/2);

    editor->setGeometry(checkboxstyle.rect);
}
