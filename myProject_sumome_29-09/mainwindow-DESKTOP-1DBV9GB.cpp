#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include "tablewidget.h"
#include "settingsdialog.h"
#include "emitter.h"
#include "curvesetting.h"
#include "QSqlQuery"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_settings(new SettingsDialog),
    m_curveSetting(new CurveSetting)

{
    ui->setupUi(this);
    QSqlTableModel *model2 = new QSqlTableModel;
    model2->setTable("data");
    model2->select();

    QTableView *tableView = new QTableView;
    tableView->setModel(model2);

    m_emitter=new Emitter;
    m_pThread = new QThread(this);
    m_emitter->moveToThread(m_pThread);
    m_pThread->start();

    createView();
    stateView=false;

    connect(ui->actionSetting_connect, &QAction::triggered, m_settings, &SettingsDialog::show);
    connect(ui->actionDevice_connect,&QAction::triggered, this,&MainWindow::openPort);
    connect(ui->actionStartLog,&QAction::triggered, this,&MainWindow::startLog);
    //connect(m_emitter,&Emitter::signal1,this,&MainWindow::test);
    connect(ui->actionCurve,&QAction::triggered,m_curveSetting,&CurveSetting::show);
    connect (m_emitter,&Emitter::getBufferSerial,this,&MainWindow::getRealData);
    connect(ui->actionSave_layout,&QAction::triggered,this,&MainWindow::saveLayout);
    connect(ui->actionLoad_layout,&QAction::triggered,this,&MainWindow::loadLayout);
    connect(ui->actionpause_logging,&QAction::triggered,this,&MainWindow::setStateView);
    for(int i=0;i<m_view.size();i++)
        connect(m_curveSetting->newButton,&QPushButton::clicked,m_view.at(i).data(),&TrackViewWidget::updateCurveAttribute);
    connect(m_curveSetting->newButton,&QPushButton::clicked,m_view2,&TrackViewWidget::updateCurveAttribute);
    connect(m_curveSetting->newButton,&QPushButton::clicked,m_view1,&TrackViewWidget::updateCurveAttribute);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openPort()
{
    m_emitter->initPort(m_settings->settings());
    startLog();
}

void MainWindow::startLog()
{
    qDebug() << "start button";
    m_emitter->start();

}

void MainWindow::openCurveAttributeDialog()
{

}

void MainWindow::createView()
{
    m_view1=new TrackViewWidget();
    m_view2=new TrackViewWidget();

    QDockWidget *dock = new QDockWidget(tr("View1"), this);
    QDockWidget *dock2 = new QDockWidget(tr("View2"), this);

    QSplitter *mainLayout =new QSplitter;
    QGridLayout *mainLayout2 = new QGridLayout;

    dock->setWidget(m_view1);
    dock2->setWidget(m_view2);
    addDockWidget(Qt::TopDockWidgetArea,dock);
    addDockWidget(Qt::TopDockWidgetArea,dock2);

    //Create VIEW
    QSqlQuery query("SELECT * FROM trackview");
    int i=0;
    while (query.next()) {
        QString str = query.value(1).toString();
        int id= query.value(0).toInt();
        QSharedPointer<TrackViewWidget> temp(new TrackViewWidget(id,"test"));
        m_view.append(temp);
        QDockWidget *dock3 = new QDockWidget(tr("view"), this);
        dock3->setWidget(m_view.at(i).data());
        addDockWidget(Qt::TopDockWidgetArea,dock3);
        i++;
     }




}

void MainWindow::loadConfig()
{

}

void MainWindow::test()
{
    qDebug() << "test";

}

void MainWindow::getRealData(QByteArray str)
{
    qDebug()<< "handle realdata";

    static QTime time(QTime::currentTime());
    double key = QDateTime::currentDateTime().toTime_t();

    if(str.size()==8){

        m_mic1=QRandomGenerator::global()->bounded(0,800);
        m_mic2=QRandomGenerator::global()->bounded(0,500);
        m_vir1=QRandomGenerator::global()->bounded(0,200);
        m_vir2=QRandomGenerator::global()->bounded(0,200);
        m_date=key;

        QSqlQuery query;
        query.prepare("INSERT INTO data (mic1,mic2,vir1,vir2,datatime) "
                      "VALUES (:mic1,:mic2,:vir1,:vir2,:datetime)");
        query.bindValue(":mic1",m_mic1);
        query.bindValue(":mic2",m_mic2);
        query.bindValue(":vir1",m_vir1);
        query.bindValue(":vir2",m_vir2);
        query.bindValue(":datetime",key);
        query.exec();

         m_view1->addDataChart(m_date,m_mic1,m_mic2);
    }
    if(str.size()==2062){

        UINT buffSum[2062], buffVib1[512], buffVib2[512];
        UINT buffMic1[512], buffMic2[512];
        UINT i, it, id = 0, ix, j, ku = 1, itemp, imax0 = 0, imax1 = 0, imax2 = 0, imax3 = 0;
        int	pTempData[1500];
        UINT iBufData[1500];
        QByteArray strBuff;

        float ft;
        i = 0;
        j = 0;
        //strBuff=str;

        while (j < 2062) {
            pTempData[i] = str[j] + str[j + 1] * 256;

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
        m_mic1=iBufData[2];
        m_mic2=iBufData[3];

        QSqlQuery query;
        query.prepare("INSERT INTO data (mic1,mic2,vir1,vir2,datatime) "
                      "VALUES (:mic1,:mic2,:vir1,:vir2,:datetime)");
        query.bindValue(":mic1",m_mic1);
        query.bindValue(":mic2",m_mic2);
        query.bindValue(":vir1",m_vir1);
        query.bindValue(":vir2",m_vir2);
        query.bindValue(":datetime",key);
        query.exec();

        m_view1->addDataChart(m_date,m_mic1,m_mic2);
        //m_view2->addDataChart(m_date,m_mic1,m_mic2);


        m_vir1=QRandomGenerator::global()->bounded(0,200);
        m_vir2=QRandomGenerator::global()->bounded(0,200);
        m_date=key;


    }

}

void MainWindow::saveLayout(){
    QString fileName
        = QFileDialog::getSaveFileName(this, tr("Save layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    QByteArray geo_data = saveGeometry();
    QByteArray layout_data = saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) {
        QString msg = tr("Error writing to %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

void MainWindow::loadLayout(){
    QString fileName
        = QFileDialog::getOpenFileName(this, tr("Load layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok) {
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok) {
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok)
        ok = restoreGeometry(geo_data);
    if (ok)
        ok = restoreState(layout_data);

    if (!ok) {
        QString msg = tr("Error reading %1").arg(QDir::toNativeSeparators(fileName));
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

void MainWindow::setStateView()
{
    stateView=!stateView;
    m_view1->setStateView(stateView);
}
