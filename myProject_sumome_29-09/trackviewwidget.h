#ifndef TRACKVIEWWIDGET_H
#define TRACKVIEWWIDGET_H

#include <QWidget>
#include <qcustomplot.h>
#include "tablemodel.h"
#include "curveattribute.h"
#include "headerwiget.h"

class TrackViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrackViewWidget(QWidget *parent = nullptr);
    TrackViewWidget(int id,QString name,QMap<QString,QSharedPointer< QCPGraphDataContainer >> listCurves);

signals:
    void moveSplitter(int pos,int index);
private:
    int m_viewID;
    const QString m_viewName;
    TableModel *m_curveAttribute;
    boolean m_stateView;
    QCustomPlot *m_CustomPlot;
    QPushButton *btnCurverAttribute;
    QPushButton *btnStateView;
    CurveAttribute *m_curveAttributeDialog;
    QMap<QString,QSharedPointer< QCPGraphDataContainer >> m_listCurves;
    QSplitter *m_splitter;
    HeaderWiget *m_header;



public:
    void setupChart();
    void updateChart();
    void updateCurveAttribute();
    void setStateView(boolean state);
    void setData(int indexGraph,QSharedPointer< QCPGraphDataContainer > container);
    void getPositionSplit(int pos, int index);
    void setHeightSplitter(int width);
    int getSizeSplitter();
    void setTextBtnStateView(QString name);

private slots:
    void btnStateView_click();
    void btnCurveAttribute_click();




};

#endif // TRACKVIEWWIDGET_H
