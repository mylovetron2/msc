#ifndef HEADERWIGET_H
#define HEADERWIGET_H

#include <QWidget>
//#include <QTableView>
#include <tablemodel.h>

class HeaderWiget : public QWidget
{
    Q_OBJECT
public:
    HeaderWiget();
    HeaderWiget(TableModel *tablemodel);

protected:
   void paintEvent(QPaintEvent *event);
   void drawLines(QPainter *qp);

public:
   TableModel *m_tablemodel;

};

#endif // HEADERWIGET_H
