#include "tablewidget.h"
#include "QTableView"
#include "mydatatable.h"

#include <QHeaderView>
#include <QtWidgets/QGridLayout>
#include "QDebug"
#include "trackview.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "QRandomGenerator"

TableWidget::TableWidget(QWidget *parent) : QWidget(parent),
  //,m_CustomPlot(new QCustomPlot(this))
  m_serial(new QSerialPort(this))
{

    my_thread = new QThread();
    m_serial->moveToThread(my_thread);
    my_thread->start();

    ConnectSerialPort();

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot2()));
    dataTimer.start(100); // Interval 0 means to refresh as fast as possible

    model = new QSqlQueryModel;
    model->setQuery("select * from data");

    modelTable=new QSqlTableModel;
    modelTable->setTable("data");
    modelTable->select();

    QTableView *tableView = new QTableView;
    tableView->setModel(modelTable);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    TrackView *trackview;
    trackview=new TrackView();
    trackview->setModel(modelTable);

    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(trackview, 1, 1);

    setLayout(mainLayout);

}

void TableWidget::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.1) // 0.002 at most add point every 2 ms
    {
      writeData();
      //model->setQuery(q);
      model->setQuery("select * from data ORDER BY id desc limit 1");
      lastPointKey = key;
    }
}

void TableWidget::realtimeDataSlot2()
{
    writeData();
    //model->setQuery("select * from data ORDER BY id desc limit 1");
    modelTable->select();
}

void TableWidget::ConnectSerialPort(){
    m_serial->setPortName("COM2");
    m_serial->setBaudRate(256000);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    m_serial->open(QIODevice::ReadWrite);

    connect(m_serial, &QSerialPort::readyRead, this, &TableWidget::readSerial);

}

void TableWidget::writeData(){

    static QByteArray data2;
    data2[0]=0xf1;
    //data2[0]=10;
    data2[1]=0;
    data2[2]=0;
    data2[3]=0;
    data2[4]=0;
    data2[5]=0;
    data2[6]=0;
    data2[7]=0;
    m_serial->write(data2);

}

void TableWidget::readSerial()
{
    //QTimer::singleShot(110,this,&TableWidget::readSerial);
    qDebug() << "ReadSerial->buffSize:"<<strReceive.size();

    //if (m_serial->waitForReadyRead(10))
        strReceive = m_serial->readAll();
        //QByteArray responseData = m_serial->readAll();
        //qDebug() << "OK";
    //else
    //    qDebug() << "fail";


    strBuff.append(strReceive);

    int	pTempData[1500];
    UINT iBufData[1500];
    //QDebug deb = qDebug();
    //deb << str;


    if(strBuff.size()==2062){
        QDebug deb = qDebug();

        //deb <<strBuff.size()<<".."<<strReceive.size();
        UINT i, it, id = 0, ix, j, ku = 1, itemp, imax0 = 0, imax1 = 0, imax2 = 0, imax3 = 0;
        float ft;
        i = 0;
        j = 0;
            while (j < 2062) {
                pTempData[i] = strBuff[j] + strBuff[j + 1] * 256;

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


        strBuff.clear();
        strReceive.clear();

        static QTime time(QTime::currentTime());
        //double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
        double key = QDateTime::currentDateTime().toTime_t();

        QSqlQuery query;
        query.prepare("INSERT INTO data (CCL, ARM1,ARM2,datatime) "
                      "VALUES (:ccl,:arm1,:arm2,:datetime)");


        double ccl=iBufData[2];
        int arm1=iBufData[3];

        //double ccl=500;
        //int arm1=200;

        int arm2=QRandomGenerator::global()->bounded(0,200);

        query.bindValue(":ccl",ccl);
        query.bindValue(":arm1",arm1);
        query.bindValue(":arm2",arm2);
        query.bindValue(":datetime",key);
        query.exec();

    }
    else if(strBuff.size()>2062){
       strBuff.clear();
       strReceive.clear();

    }
    else
        return;


}
