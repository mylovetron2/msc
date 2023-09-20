#ifndef MSCPOLARVIEW_H
#define MSCPOLARVIEW_H

#include <QWidget>
#include <qcustomplot.h>

class MSCPolarView : public QWidget
{
   Q_OBJECT

public:
    explicit MSCPolarView(QWidget *parent = nullptr);
    MSCPolarView(int maxArm);
    void CreateChart();
    void UpdateData(QMap<double,double> map);
    void SetMaxArm(int maxArm);
    void openArm();
    void closeArm();
    void stopArm();

private:
    QCustomPlot *m_CustomPlot;
    int m_MaxArm;
    QCPPolarGraph *m_graph;
    QPushButton *btnOpenArm;
    QPushButton *btnCloseArm;
    QPushButton *btnStopArm;
    int m_stateArm; // 1:open -1:close 0:stop

signals:
    void openArm_sig();
    void closeArm_sig();
    void stopArm_sig();

};


#endif // MSCPOLARVIEW_H
