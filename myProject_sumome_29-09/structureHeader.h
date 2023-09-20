#ifndef STRUCTUREHEADER_H
#define STRUCTUREHEADER_H

#include <QObject>
#include <QSerialPort>

typedef struct {
    QString name;
    qint32 baudRate;
    QString stringBaudRate;
    QSerialPort::DataBits dataBits;
    QString stringDataBits;
    QSerialPort::Parity parity;
    QString stringParity;
    QSerialPort::StopBits stopBits;
    QString stringStopBits;
    QSerialPort::FlowControl flowControl;
    QString stringFlowControl;
    bool localEchoEnabled;
} Settings;

Q_DECLARE_METATYPE(Settings);

#endif // STRUCTUREHEADER_H
