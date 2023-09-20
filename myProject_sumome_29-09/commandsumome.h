#ifndef COMMANDSUMOME_H
#define COMMANDSUMOME_H

#include "command.h"
#include <QMap>

class CommandSumome:public Command
{

public:
    CommandSumome();
    //QMap<QString, int> readSerial(QString strR) override;
    QString getName() override;
    int getSizeBuffer() override;
    void setData(QByteArray strR) override;

};


#endif // COMMANDSUMOME_H
