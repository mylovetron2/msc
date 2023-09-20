#ifndef COMMANDDMT_H
#define COMMANDDMT_H
#include "command.h"

class CommandDMT : public Command
{

public:
    double m_fEncoderConst;

    CommandDMT();
    //QMap<QString,int> readSerial(QString strR) override;
    QString getName() override;
    int getSizeBuffer() override;
    void setData(QByteArray strR) override;

private slots:
    void updateFEncoderConst(double f);
};

#endif // COMMANDDMT_H
