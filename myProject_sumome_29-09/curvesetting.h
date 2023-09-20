#ifndef CURVESETTING_H
#define CURVESETTING_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>

class CurveSetting : public QWidget
{
    Q_OBJECT
public:
    explicit CurveSetting(QWidget *parent = nullptr);
    void createWidgets();
    void createGUI();

signals:

private:
    QSqlTableModel *model;
    QTableView *tableView;
public:
    QPushButton *newButton;


};

#endif // CURVESETTING_H
