#ifndef EMITTER_H
#define EMITTER_H

#include <QObject>
#include <QSerialPort>
#include "structureHeader.h"
#include <QTimer>
#include <qcustomplot.h>
#include <command.h>

class Emitter : public QObject
{
    Q_OBJECT
public:
    explicit Emitter(QObject *parent = nullptr);

signals:
    void signal1();
    void getBufferSerial(QByteArray);
    void updateData();
    void updateAllData();
    void readSerial_sig(QByteArray);

private:
    QSerialPort *m_serial;
    QTimer *m_pTimer;
    QMutex m_mutex;
    QByteArray strBuff;
    QByteArray strReceive;
    QList<Command*> m_listCommand;
    int m_CurrentCommand;

public:
    void initPort(Settings setting);
    void start();
    void stop();
    void addCommand(Command *cmd);
    void removeLastCommand();
    QList<QString> getAllNameChannel();
    QMap<QString,double> getAllDataChannel();
    QMap<QString,double> getDataCurrentCommand();


public slots:
    void readSerial();
    void writeSerial();
    void handleReadSerial(QByteArray r);
};

#endif // EMITTER_H
