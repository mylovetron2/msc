#include "command.h"
#include "QDataStream"

Command::Command()
{
    m_dataWrite.resize(8);
}

Command::~Command()
{

}


QByteArray Command::dataWrite()
{
    return m_dataWrite;
}



QMap<QString, double> Command::getData()
{
    return m_data;
}

