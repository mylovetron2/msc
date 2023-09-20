#include "commandmsc.h"
#include "QDebug"
#include "QDataStream"

#define maxArm 40

commandmsc::commandmsc()
{

    m_dataWrite.resize(8);
    /* Test MSC
    m_dataWrite[0]=0xcc;
    m_dataWrite[1]=0x10;
    m_dataWrite[2]=0x5f;
    m_dataWrite[3]=48;
    m_dataWrite[4]=59;
    m_dataWrite[5]=172;
    m_dataWrite[6]=152;
    m_dataWrite[7]=0;*/

    m_dataWrite[0]=0xcc;
    m_dataWrite[1]=0x10;
    m_dataWrite[2]=0x00;
    m_dataWrite[3]=48;        //48  0x30
    m_dataWrite[4]=59;         //59 0x3b
    m_dataWrite[5]=172;       //172 0xac
    m_dataWrite[6]=152;       //152 0x98
    m_dataWrite[7]=75;        //75

    for(int i=1;i<maxArm+1;i++){
       if(i<10)
            m_data.insert("AM0"+QString::number(i),0);
       else
           m_data.insert("AM"+QString::number(i),0);
   }
}

QString commandmsc::getName()
{
    return "Msc";
}

int commandmsc::getSizeBuffer()
{
    return 98;    //98  //138
}

void commandmsc::setData(QByteArray strR)
{
    if(strR.size()==98)
    {    //98
        if(strR.at(96)==16)
        {
            qDebug()<<"MSC Good";
            int j=0;
            QByteArray arr;
            arr.resize(2);
            bool ok;
            uint val;
            //val=100;

            for(int i=1;i<maxArm+1;i++){

                //arr[0]=strR[j];
                //arr[1]=strR[j+1];

                arr[0]=strR.at(j);
                arr[1]=strR.at(j+1);
                //qDebug()<<strR.at(j)<<"-"<<strR.at(j+1);

                memcpy(&val,arr.constData(),2);

                //qDebug()<<val;

                if(i<10)
                    //m_data["AM0"+QString::number(i)]=strR[j]+strR[j+1]*256;
                   m_data["AM0"+QString::number(i)]=val;

                else
                   //m_data["AM"+QString::number(i)]=strR[j]+strR[j+1]*256;
                    m_data["AM"+QString::number(i)]=val;

                j=j+2;
            }
        }
    }
}

