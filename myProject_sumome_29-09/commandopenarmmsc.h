#ifndef COMMANDOPENARMMSC_H
#define COMMANDOPENARMMSC_H

//#include <QObject>
#include "command.h"


class CommandOpenArmMSC:public Command
{
public:
    CommandOpenArmMSC();
    QString getName() override;
    int getSizeBuffer() override;
    void setData(QByteArray strR) override;
};

#endif // COMMANDOPENARMMSC_H
