#include "emitter.h"
#include "QDebug"
#include <QThread>
#include <QSqlQuery>
#include "commandsumome.h"
#include "commanddmt.h"


#define timeOut 333

Emitter::Emitter(QObject *parent) : QObject(parent)
{
    m_CurrentCommand=-1;
    m_serial=new QSerialPort();
    QThread *innerThread;
    innerThread = new QThread(this);
    m_serial->moveToThread(innerThread);
    innerThread->start();

    m_pTimer = new QTimer();
    connect(m_pTimer, &QTimer::timeout, this,&Emitter::writeSerial);
}

void Emitter::initPort(Settings setting)
{
    //const Settings p = m_settings->settings();
    m_serial->setPortName(setting.name);
    m_serial->setBaudRate(setting.baudRate);
    m_serial->setDataBits(setting.dataBits);
    m_serial->setParity(setting.parity);
    m_serial->setStopBits(setting.stopBits);
    m_serial->setFlowControl(setting.flowControl);

    if (m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "port opened";
        qDebug() << m_serial->portName();
        qDebug() << m_serial->baudRate();
        qDebug() << m_serial->dataBits();
        qDebug() << m_serial->parity();
        qDebug() << m_serial->stopBits();
        qDebug() << m_serial->flowControl();

        //connect(m_serial, &QSerialPort::readyRead, this, &Emitter::readSerial);
        //connect(this, &Emitter::readSerial_sig, this, &Emitter::handleReadSerial);


    } else {
        qDebug() << "open port error";

    }

}

void Emitter::start()
{
   qDebug() << "Emitter start";
   //m_pTimer = new QTimer();
   //connect(m_pTimer, &QTimer::timeout, this,&Emitter::writeSerial);
   m_pTimer->start(timeOut);
}

void Emitter::stop()
{
    m_pTimer->stop();
}

void Emitter::addCommand(Command *cmd)
{
    m_listCommand.append(cmd);
}

void Emitter::removeLastCommand()
{
    stop();
    if(!m_listCommand.isEmpty())
        //if(m_CurrentCommand!=m_listCommand.size()-1)
        {
            m_CurrentCommand=0;
            m_listCommand.removeLast();
            //qDebug()<<"stop arm";
        }
    start();
}

QList<QString> Emitter::getAllNameChannel()
{
    QList<QString> temp;
    for(int i=0;i<m_listCommand.size();i++){
        temp.append(m_listCommand.at(i)->getData().keys());
    }
    return temp;
}

QMap<QString, double> Emitter::getAllDataChannel()
{
    QMap<QString,double> map;
    for(int i=0;i<m_listCommand.size();i++){
        if(m_listCommand.at(i)->getName()!="control")
            map.insert(m_listCommand.at(i)->getData());
    }
    return map;
}

QMap<QString, double> Emitter::getDataCurrentCommand()
{
    QMap<QString,double> map;
    //for(int i=0;i<m_listCommand.size();i++){
        if(m_listCommand.at(m_CurrentCommand)->getName()!="control")
            map.insert(m_listCommand.at(m_CurrentCommand)->getData());
    //}
    return map;
}

/*
void Emitter::writeSerial(){
    if(m_CurrentCommand==m_listCommand.size()-1){
        m_CurrentCommand=0;
        //emit updateData();
         emit updateAllData();
    }
    else
        m_CurrentCommand++;

    m_serial->write(m_listCommand.at(m_CurrentCommand)->dataWrite());

    //if (m_serial->waitForBytesWritten(10)){
       // read response
        //if (m_serial->waitForReadyRead(10000))
        {
            QByteArray responseData;
            int isize=0;
            while (m_serial->bytesAvailable() && isize<m_listCommand.at(m_CurrentCommand)->getSizeBuffer())
            {
                isize++;
                responseData += m_serial->readAll();
            }
            emit this->handleReadSerial(responseData);

        }

}
*/

void Emitter::handleReadSerial(QByteArray str)
{
    if(m_CurrentCommand!=-1)
    {
        if(str.size()==m_listCommand.at(m_CurrentCommand)->getSizeBuffer()) {
            //qDebug() <<"read Serial: "<<m_listCommand.at(m_CurrentCommand)->getName();
            m_listCommand.at(m_CurrentCommand)->setData(str);
            emit getBufferSerial("sumome");

        }
     }
}


void Emitter::readSerial()
{
    QByteArray strReceive;
    QByteArray strBuff;
    if(m_serial->waitForReadyRead(30))
        strReceive = m_serial->readAll();

    strBuff.append(strReceive);
    //qDebug() <<m_CurrentCommand;
    if(m_CurrentCommand!=-1)
    {
        int temp=strBuff.size();
        unsigned  char b1= strBuff.at(136);
        unsigned char b2=strBuff.at(137);
        if(strBuff.size()==138 && b1==170 && b2==170){
            m_listCommand.at(0)->setData(strBuff);
        }
        else if(strBuff.size()==m_listCommand.at(m_CurrentCommand)->getSizeBuffer())
        {
            //qDebug() <<"read Serial: "<<m_listCommand.at(m_CurrentCommand)->getName();
            m_listCommand.at(m_CurrentCommand)->setData(strBuff);
            emit getBufferSerial("sumome");

        }
       //else
            //return;
    }
}

/*
void Emitter::writeSerial()
{

    strBuff.clear();
    strReceive.clear();
    if(m_CurrentCommand==m_listCommand.size()-1){
        m_CurrentCommand=1;
        //emit updateData();
         emit updateAllData();
    }
    else
        m_CurrentCommand++;
    m_serial->write(m_listCommand.at(m_CurrentCommand)->dataWrite());

}*/

void Emitter::writeSerial()
{
    if(m_CurrentCommand==m_listCommand.size()-1){
        m_CurrentCommand=0;
        //emit updateData();
         emit updateAllData();
    }
    else
        m_CurrentCommand++;

    //if(m_CurrentCommand==0)
     //   m_serial->setParity(static_cast<QSerialPort::Parity>(0));
    //else
        //m_serial->setParity(static_cast<QSerialPort::Parity>(2));

    m_serial->write(m_listCommand.at(m_CurrentCommand)->dataWrite());



    qDebug()<<"Hoi " <<m_listCommand.at(m_CurrentCommand)->getName();

    if(m_listCommand.at(m_CurrentCommand)->getName()!="control")
    {
        if(m_serial->waitForBytesWritten(10))
        {
            // read response
            //if (m_serial->waitForReadyRead(1))
            {
                QByteArray responseData = m_serial->readAll();
                //QByteArray responseData = m_serial->read(m_listCommand.at(m_CurrentCommand)->getSizeBuffer());
                if(m_CurrentCommand==1){
                    int temp ;
                    temp=0;
                }
                while (m_serial->waitForReadyRead(10))
                    responseData += m_serial->readAll();
                m_listCommand.at(m_CurrentCommand)->setData(responseData);
                emit getBufferSerial("sumome");
                if(responseData.size()== m_listCommand.at(m_CurrentCommand)->getSizeBuffer())
                    qDebug()<< m_listCommand.at(m_CurrentCommand)->getName();
                else
                    qDebug()<<"size buff "<< responseData.size() << "error _"+ m_listCommand.at(m_CurrentCommand)->getName();
            }
            //else
                //qDebug()<<"time out" +m_listCommand.at(m_CurrentCommand)->getName();
        }
        //else
            //qDebug()<<"time out waitForBytesWritten";
    }
    else
        qDebug()<<"control";
}

/*
void Emitter::writeSerial()
{
    if(m_CurrentCommand==m_listCommand.size()-1){
        m_CurrentCommand=0;
        //emit updateData();
         emit updateAllData();
    }
    else
        m_CurrentCommand++;
    m_serial->write(m_listCommand.at(m_CurrentCommand)->dataWrite());
    qDebug()<<"Hoi " <<m_listCommand.at(m_CurrentCommand)->getName();

    if(m_listCommand.at(m_CurrentCommand)->getName()!="control")
    {
        if(m_serial->waitForBytesWritten(1)){
            // read response
            //if (m_serial->waitForReadyRead(1))
            {
                QByteArray responseData = m_serial->readAll();
                //QByteArray responseData = m_serial->read(m_listCommand.at(m_CurrentCommand)->getSizeBuffer());

                while (m_serial->waitForReadyRead(10))
                    responseData += m_serial->readAll();
                m_listCommand.at(m_CurrentCommand)->setData(responseData);
                emit getBufferSerial("sumome");
                if(responseData.size()== m_listCommand.at(m_CurrentCommand)->getSizeBuffer())
                    qDebug()<< m_listCommand.at(m_CurrentCommand)->getName();
                else
                    qDebug()<<"size buff "<< responseData.size() << "error _"+ m_listCommand.at(m_CurrentCommand)->getName();
            }
            //else
                //qDebug()<<"time out" +m_listCommand.at(m_CurrentCommand)->getName();
        }
        else
            qDebug()<<"time out waitForBytesWritten";
    }
    else
        qDebug()<<"control";
}
*/
