#ifndef COMMAND_H
#define COMMAND_H
#include <QObject>
#include <QByteArray>
#include <QString>
#include <QMap>


class Command
{

protected:
    QByteArray m_dataWrite;

    QString m_name;
    QMap<QString, double> m_data;

public:
    Command();
    ~Command();

    QByteArray dataWrite();

    virtual QString getName()=0;
    //virtual QMap<QString, int> readSerial(QString strR)=0;
    QMap<QString, double> getData();
    virtual void setData(QByteArray strR)=0;
    virtual int getSizeBuffer()=0;

signals:
    void updateData();
};

#endif // COMMAND_H
