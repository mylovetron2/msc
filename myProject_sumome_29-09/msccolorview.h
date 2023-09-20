#ifndef MSCCOLORVIEW_H
#define MSCCOLORVIEW_H

#include <QWidget>
#include <qcustomplot.h>

class MSCColorView: public QWidget
{
    Q_OBJECT

public:
    MSCColorView(QWidget *parent = nullptr);
    void CreateChart();
    void UpdateData(QMap<QString,QSharedPointer< QCPGraphDataContainer >> listCurves);
    void SetMaxArm(int maxArm);
    void RowData(int rowData);

private:
    QCustomPlot *m_CustomPlot;
    int m_MaxArm;
    QCPColorMap *m_graph;
    int m_rowData;
    QCPColorMapData *m_data;
    int m_intervalView;  // khoang cach xem tinh bang phut
    int m_countData;
};

#endif // MSCCOLORVIEW_H
