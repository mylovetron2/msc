#include "commanddmt.h"


CommandDMT::CommandDMT()
{
    m_fEncoderConst=1972.58436;

    m_dataWrite[0]=0xde;
    m_dataWrite[1]=0;
    m_dataWrite[2]=0;
    m_dataWrite[3]=0;
    m_dataWrite[4]=0;
    m_dataWrite[5]=0;
    m_dataWrite[6]=0;
    m_dataWrite[7]=0;

    m_data.insert("depth",0);
    m_data.insert("vol_ac",0);
    m_data.insert("amp_ac",0);
    m_data.insert("tension",0);
    m_data.insert("speed",0);
}


QString CommandDMT::getName()
{
     return "DMT";
}

int CommandDMT::getSizeBuffer()
{
    return 138;
}


void CommandDMT::setData(QByteArray strR)
{
    double	fEncoderConst=m_fEncoderConst;

    //uint i,j,ui,isiz=138;
    uint it;
    int id=0;
    short idt=0;
    double ft;
    uint val;
    QByteArray arr;
    arr.resize(2);
    //int pTempDataDMT[1500];
    //uint iBufData[1500];

    if(strR.size()==138)
    //if((strR[isiz-2] == 0xaa) &&(strR[isiz-1] == 0xaa) )	//98 bytes
    {

        //get depth
        id = strR[19]<<24;
        id += strR[18]<<16;
        id += strR[17]<<8;
        id += strR[16];
        m_data["depth"]=id;               //iDepth=id
        m_data["depth"] /= fEncoderConst;

        //get Speed
        it = strR[37]<<24;
        it += strR[36]<<16;
        it += strR[35]<<8;
        it += strR[34];
        m_data["speed"] = it;
        m_data["speed"] /= fEncoderConst;	//luu toc do
        m_data["speed"] *=10;

        //get volt AC
        //int8_t tempAC= strR[24] + strR[25]*256;
        arr[0]=strR[24];
        arr[1]=strR[25];
        memcpy(&val,arr.constData(),2);
        //ft =double(tempAC);
        //m_data["vol_ac"] = ft;
        m_data["vol_ac"]=val;


        //get ampe AC
        arr[0]=strR[26];
        arr[1]=strR[27];
        memcpy(&val,arr.constData(),2);
        //ft = strR[26] + strR[27]*256;
        //m_data["amp_ac"] = ft;
        m_data["amp_ac"]=val;

        //get tension
        ft = strR[20] + strR[21]*256;
        m_data["tension"]  = ft;

        //get ADC 6
        //ft *= 5.0/1024.0;
        //idt = strR[33]<<8;
        //idt += strR[32];
        //iDepth = id;
    }
}

void CommandDMT::updateFEncoderConst(double f)
{
    m_fEncoderConst=f;
}
