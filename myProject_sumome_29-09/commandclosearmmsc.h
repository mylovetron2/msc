#ifndef COMMANDCLOSEARMMSC_H
#define COMMANDCLOSEARMMSC_H

#include "command.h"


class CommandCloseArmMSC:public Command
{
public:
    CommandCloseArmMSC();
    QString getName() override;
    int getSizeBuffer() override;
    void setData(QByteArray strR) override;
};

#endif // COMMANDCLOSEARMMSC_H
