#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <qcustomplot.h>
#include <QSerialPort>
#include <QSqlTableModel>

class TableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidget(QWidget *parent = nullptr);

signals:
private:
    void ConnectSerialPort();
    //QCustomPlot *m_CustomPlot;
    //CustomSqlModel *model;
    QSqlQueryModel *model;
    QSqlTableModel *modelTable;

    QTimer dataTimer;
    QSerialPort *m_serial = nullptr;
    QThread *my_thread;

    UINT buffSum[2062], buffVib1[512], buffVib2[512], buffMic1[512], buffMic2[512];
    QByteArray strBuff;
    QByteArray strReceive;

private slots:
    void realtimeDataSlot();
    void realtimeDataSlot2();
    void readSerial();
    void writeData();
};

#endif // TABLEWIDGET_H
