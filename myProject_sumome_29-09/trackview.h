#ifndef TRACKVIEW_H
#define TRACKVIEW_H

#include <QObject>
#include <QAbstractItemView>
#include <qcustomplot.h>
#include <QtWidgets>
#include <curvesetting.h>
#include <tablemodel.h>

class TrackView: public QAbstractItemView

{

public:
    TrackView(QWidget *parent = nullptr) ;
    void setupChart();
private:
    QCustomPlot *m_CustomPlot;
    QVBoxLayout *layout;
    //TableModel *m_Model;
/* BEGIN QAbstractItemView interface */
public:
   void paintEvent(QPaintEvent *event) override;
   //virtual void setModel(QAbstractItemModel *model);
   virtual QRect visualRect(const QModelIndex &index) const;
   virtual void scrollTo(const QModelIndex &index,ScrollHint hint=EnsureVisible);
   virtual QModelIndex indexAt(const QPoint &point) const;
protected:
   virtual QModelIndex moveCursor(CursorAction cursorAction,Qt::KeyboardModifiers modifiers);
   virtual int horizontalOffset() const;
   virtual int verticalOffset() const;
   virtual bool isIndexHidden(const QModelIndex &index) const;
   virtual void setSelection(const QRect &rect,QItemSelectionModel::SelectionFlags command);
   virtual QRegion visualRegionForSelection(const QItemSelection &selection) const;
   virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
/* END QAbstractItemView interface */
public slots:
   void updateSettingChar();
};

#endif // TRACKVIEW_H
