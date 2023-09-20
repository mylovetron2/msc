#include "commandclosearmmsc.h"

CommandCloseArmMSC::CommandCloseArmMSC()
{
    m_dataWrite[0]=0xcc;
    m_dataWrite[1]=0x10;
    m_dataWrite[2]=0x50;
    m_dataWrite[3]=48;
    m_dataWrite[4]=59;
    m_dataWrite[5]=172;
    m_dataWrite[6]=152;
    m_dataWrite[7]=75;

    m_data.insert("temp",0);
}

QString CommandCloseArmMSC::getName()
{
    return "control";
}

int CommandCloseArmMSC::getSizeBuffer()
{
    return 0;
}

void CommandCloseArmMSC::setData(QByteArray strR)
{
    m_data["temp"]=0;
}
