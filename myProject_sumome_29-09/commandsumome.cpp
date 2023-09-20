#include "commandsumome.h"


CommandSumome::CommandSumome()
{
    /*
    m_dataWrite[0]=0xf0;
    m_dataWrite[1]=0;
    m_dataWrite[2]=0;
    m_dataWrite[3]=0;
    m_dataWrite[4]=0;
    m_dataWrite[5]=0;
    m_dataWrite[6]=0;
    m_dataWrite[7]=0;*/

    m_dataWrite[0]=0xde;
    m_dataWrite[1]=0;
    m_dataWrite[2]=0;
    m_dataWrite[3]=0;
    m_dataWrite[4]=0;
    m_dataWrite[5]=0;
    m_dataWrite[6]=0;
    m_dataWrite[7]=0;

    /*
    m_dataWrite[0]=0xcc;
    m_dataWrite[1]=0x10;
    m_dataWrite[2]=0xa0;
    m_dataWrite[3]=48;
    m_dataWrite[4]=59;
    m_dataWrite[5]=172;
    m_dataWrite[6]=152;
    m_dataWrite[7]=0;*/

    m_data.insert("mic1",0);
    m_data.insert("mic2",0);
    m_data.insert("vir1",0);
    m_data.insert("vir2",0);

}

QString CommandSumome::getName()
{
    return "Sumome";
}

int CommandSumome::getSizeBuffer()
{
    return 2062;
}

void CommandSumome::setData(QByteArray strR)
{
    if(strR.size()==2062){

        uint buffSum[2062], buffVib1[512], buffVib2[512];
        uint buffMic1[512], buffMic2[512];
        uint i, it, id = 0, ix, j, ku = 1, itemp, imax0 = 0, imax1 = 0, imax2 = 0, imax3 = 0;
        int	pTempData[1500];
        uint iBufData[1500];
        QByteArray strBuff;

        float ft;
        i = 0;
        j = 0;
        //strBuff=str;

        while (j < 2062) {
            pTempData[i] = strR[j] + strR[j + 1] * 256;
            j = j + 2;
            i++;
        }

        for (i = 0; i < 1024; i++) {
            if((i + 1) % 2)
                buffVib1[i / 2] = pTempData[i];
            else
                buffVib2[(i - 1) / 2] = pTempData[i];
        }

        iBufData[2] = pTempData[1026];//pTempDataAK1[64];	//UAE
        iBufData[3] = pTempData[1027];//pTempDataAK1[65];	//UAE
        iBufData[4] = pTempData[1028];//pTempDataAK1[64];	//UAE
        iBufData[5] = pTempData[1029];//pTempDataAK1[65];	//UA

        for (int t = 0; t < 512; t++)
        {
            if (buffVib1[t] > iBufData[2])
                iBufData[2] = buffVib1[t];

            if (buffVib2[t] > iBufData[3])
                iBufData[3] = buffVib2[t];
        }
        //m_data["mic1"]=iBufData[2];
        //m_data["mic2"]=iBufData[3];

        m_data["mic1"]=iBufData[2];
        m_data["mic2"]=iBufData[3];
        m_data["vir1"]=400;
        m_data["vir2"]=800;

    }

}
