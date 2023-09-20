#ifndef COMMANDMSC_H
#define COMMANDMSC_H

#include "command.h"

class commandmsc:public Command
{
public:
    commandmsc();
    QString getName() override;
    int getSizeBuffer() override;
    void setData(QByteArray strR) override;
};

#endif // COMMANDMSC_H
