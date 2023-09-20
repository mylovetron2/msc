#ifndef DATATABLEVIEW_H
#define DATATABLEVIEW_H


#include <QWidget>
#include <QTableView>

class DataTableView : public QWidget
{
    Q_OBJECT
private:
    QTableView *tableView;
public:
    DataTableView();

};

#endif // DATATABLEVIEW_H
