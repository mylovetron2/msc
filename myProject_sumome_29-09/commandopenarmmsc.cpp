#include "commandopenarmmsc.h"

CommandOpenArmMSC::CommandOpenArmMSC()
{
    m_dataWrite[0]=0xcc;
    m_dataWrite[1]=0x10;
    m_dataWrite[2]=0xa0;
    m_dataWrite[3]=48;
    m_dataWrite[4]=59;
    m_dataWrite[5]=172;
    m_dataWrite[6]=152;
    m_dataWrite[7]=0;

    m_data.insert("temp",0);

}

QString CommandOpenArmMSC::getName()
{
    return "control";
}

int CommandOpenArmMSC::getSizeBuffer()
{
    return 0;
}

void CommandOpenArmMSC::setData(QByteArray strR)
{
    m_data["temp"]=0;
}
