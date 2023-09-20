#include "comboboxcolordelegate.h"
#include <QSpinBox>
#include <QComboBox>

ComboBoxColorDelegate::ComboBoxColorDelegate(QObject *parent)
{

}

QWidget *ComboBoxColorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    //editor->setFrame(false);
    //editor->setMinimum(0);
    //editor->setMaximum(100);
    const QStringList colorNames = QColor::colorNames();

    for (int i = 0; i < colorNames.size(); ++i) {
        QColor color(colorNames[i]);

        editor->insertItem(i, colorNames[i]);
        editor->setItemData(i, color, Qt::DecorationRole);
    }

    return editor;
}

void ComboBoxColorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

     //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
     //spinBox->setValue(value);
    QComboBox *comboBox=static_cast<QComboBox*>(editor);
    //comboBox->setValue(value);
    comboBox->setCurrentText(value);
    //comboBox->showPopup();
}

void ComboBoxColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox= static_cast<QComboBox*>(editor);
    //comboBox->interpretText();
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
    //model->setData(index, value, Qt::DecorationRole);
}

void ComboBoxColorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
