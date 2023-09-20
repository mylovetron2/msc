#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include "tablewidget.h"
#include "settingsdialog.h"
#include "parameterdialog.h"

#include "emitter.h"
#include "curvesetting.h"
#include "QSqlQuery"
#include "QSqlRecord";
#include "commandsumome.h"
#include "commanddmt.h"
#include "commandmsc.h"
#include "commandopenarmmsc.h"
#include "commandclosearmmsc.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_settings(new SettingsDialog),
    m_loaddata(new loaddata),
    m_curveSetting(new CurveSetting),
    m_dataTable(new QTableWidget),
    m_dmtview(new DMTView),
    m_parameter(new ParameterDialog)

{
    ui->setupUi(this);

    m_maxArm=40;

    QSqlTableModel *model2 = new QSqlTableModel;
    model2->setTable("data");
    model2->select();

    QTableView *tableView = new QTableView;
    tableView->setModel(model2);

    m_emitter=new Emitter;
    m_pThread = new QThread(this);
    m_emitter->moveToThread(m_pThread);
    m_pThread->start();

    Command *cmdSumome=new CommandSumome();
    Command *cmdDMT=new CommandDMT();
    Command *cmdMSC=new commandmsc();

    //m_emitter->addCommand(cmdMSC);
    //m_emitter->addCommand(cmdDMT);
    //m_emitter->addCommand(cmdDMT);
    m_emitter->addCommand(cmdMSC);

    //m_emitter->addCommand(cmdMSC);
    //m_emitter->addCommand(cmdMSC);

   // Khoi tao listCurves
   for(QString name :m_emitter->getAllNameChannel()){
       QSharedPointer<QCPGraphDataContainer> channel= QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
       listCurves.insert(name,channel);
    }

    createView();
    //stateView=false;

    //load layout
    QSettings settings("MySoft", "Star Runner");
    restoreGeometry(settings.value("myWidget/geometry").toByteArray());
    restoreState(settings.value("myWidget/windowState").toByteArray());

    connect(ui->actionSetting_connect, &QAction::triggered, m_settings, &SettingsDialog::show);
    connect(ui->actionParameter, &QAction::triggered, m_parameter, &ParameterDialog::show);

    connect(ui->actionLoad_data, &QAction::triggered, m_loaddata, &loaddata::show);
    connect(ui->actionDevice_connect,&QAction::triggered, this,&MainWindow::openPort);
    connect(ui->actionDisconnect,&QAction::triggered, this,&MainWindow::stopLog);
    connect(ui->actionCurve,&QAction::triggered,m_curveSetting,&CurveSetting::show);
    connect (m_emitter,&Emitter::getBufferSerial,this,&MainWindow::getRealData);
    connect(ui->actionSave_layout,&QAction::triggered,this,&MainWindow::saveLayout);
    connect(ui->actionLoad_layout,&QAction::triggered,this,&MainWindow::loadLayout);
    for(int i=0;i<m_view.size();i++)
        connect(m_curveSetting->newButton,&QPushButton::clicked,m_view.at(i).data(),&TrackViewWidget::updateCurveAttribute);
    connect (m_emitter,&Emitter::updateAllData,this,&MainWindow::updateAllData);
    connect(this->m_mscpolar,&MSCPolarView::openArm_sig,this,&MainWindow::openArm);
    connect(this->m_mscpolar,&MSCPolarView::stopArm_sig,this,&MainWindow::stopArm);
    connect(this->m_mscpolar,&MSCPolarView::closeArm_sig,this,&MainWindow::closeArm);
    connect(this->m_loaddata,&loaddata::loaddata_sig,this,&MainWindow::loadData);
}

MainWindow::~MainWindow()
{
    m_pThread->quit();
    m_dmtview->close();
    delete ui;
}

void MainWindow::openPort()
{
    m_emitter->initPort(m_settings->settings());
    startLog();
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("h:m");
    m_nameDataTable = QDateTime::currentDateTime().toString("ddMMyyyy_HH_mm_ss");
    m_nameDataTable ="data_"+m_nameDataTable;
    QList<QString> lstName=m_emitter->getAllNameChannel();

    QString s;
    s=s+"(id INTEGER PRIMARY KEY AUTOINCREMENT,";
    for(int i=0;i<lstName.size();i++) {
        s=s+lstName.at(i)+" REAL,";
    }
    s=s+"name TEXT,datetime DATETIME)";

    QSqlQuery query("CREATE TABLE ["+m_nameDataTable+"]"+ s);
    //qDebug()<< "CREATE TABLE ["+m_nameDataTable+"]"+ s;
    if(!query.isActive())
        statusBar()->showMessage("ERROR SAVE DATA:ERROR CREATE TABLE DATA");
        //qDebug() << "ERROR SAVE DATA:ERROR CREATE TABLE DATA";


}

void MainWindow::startLog()
{
    qDebug() << "start button";
    m_emitter->start();

}

void MainWindow::stopLog()
{
    m_emitter->stop();
}


void MainWindow::openCurveAttributeDialog()
{

}

void MainWindow::createView()
{
    m_view.clear();
    QHBoxLayout *content=new QHBoxLayout(this);
    //Create VIEW
    QSqlQuery query("SELECT * FROM trackview");
    int i=0;
    while (query.next()) {
        //QString str = query.value(1).toString();
        int id= query.value(0).toInt();
        QSharedPointer<TrackViewWidget> temp(new TrackViewWidget(id,"curve",listCurves));
        //QSharedPointer<TrackViewWidget> temp(new TrackViewWidget(id,"curve"));

        temp->updateCurveAttribute();
        m_view.append(temp);
        QDockWidget *dock3 = new QDockWidget(tr("view"), this);
        dock3->setWidget(m_view.at(i).data());
        addDockWidget(Qt::TopDockWidgetArea,dock3);
        //addToolBar(Qt::TopToolBarArea,dock3);
        connect(m_view.at(i).data(), &TrackViewWidget::moveSplitter, this, &MainWindow::updateSplitter);
        i++;
     }

    //create dmtview
    QDockWidget *dockDMT=new QDockWidget(tr("DMT"),this);
    m_dmtview=new DMTView();
    dockDMT->setWidget(m_dmtview);
    //dockDMT->setAllowedAreas(Qt::AllDockWidgetAreas);
    //dockDMT->setFeatures(QDockWidget::DockWidgetMovable);
    addDockWidget(Qt::TopDockWidgetArea,dockDMT);
    m_myMenu=menuBar()->addMenu(tr("&View"));
    m_myMenu->addAction(dockDMT->toggleViewAction());

    //m_dmtview->setWindowFlags(m_dmtview->windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    //m_dmtview->show();

    //create dataTable
    QDockWidget *dockTable=new QDockWidget(tr("data table"),this);
    m_dataTable->setColumnCount(2);
    m_dataTable->setShowGrid(true);
    m_dataTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_dataTable->setHorizontalHeaderLabels(QStringList()<<"name"<<"data");
    m_dataTable->horizontalHeader()->setStretchLastSection(true);
    m_dataTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:darkblue;color:white}");

    //m_dataTable->hideColumn(0);
    dockTable->setWidget(m_dataTable);
    addDockWidget(Qt::TopDockWidgetArea,dockTable);
    //m_myMenu=menuBar()->addMenu(tr("&View"));
    m_myMenu->addAction(dockTable->toggleViewAction());

    //create mscpolar
     QDockWidget *dockMscPolar=new QDockWidget(tr("msc view"),this);
     m_mscpolar=new MSCPolarView();
     dockMscPolar->setWidget(m_mscpolar);
     addDockWidget(Qt::TopDockWidgetArea,dockMscPolar);
     m_myMenu->addAction(dockMscPolar->toggleViewAction());

     //create msccolor
     QDockWidget *dockMscColor=new QDockWidget(tr("color view"),this);
     m_msccolor=new MSCColorView();
     dockMscColor->setWidget(m_msccolor);
     addDockWidget(Qt::TopDockWidgetArea,dockMscColor);
     m_myMenu->addAction(dockMscColor->toggleViewAction());

}

void MainWindow::loadConfig()
{

}

void MainWindow::test(int pos,int index)
{



}

void MainWindow::getRealData(QByteArray str)
{
    //qDebug()<< "handle realdata";
    static QTime time(QTime::currentTime());
    double key = QDateTime::currentDateTime().toTime_t();
    m_date=key;
    QMap<QString,double> map=m_emitter->getDataCurrentCommand();
    QMapIterator<QString, double> it(map);
    while (it.hasNext()) {
        it.next();
        //save to database
        //..........
        //add listCurves
        listCurves[it.key()]->add(QCPGraphData(m_date,map[it.key()]));
    }

    //Update chart
    for(int i=0;i<m_view.size();i++)
        m_view.at(i).data()->updateChart();
}

void MainWindow::loadData(QString nameTable)
{
    //qDeleteAll(listCurves);
    //listCurves.clear();

    int numTasks;
    QString s2="SELECT count(id)  FROM "+nameTable;
    QSqlQuery query2(s2);
    while(query2.next())
        numTasks=query2.record().value(0).toInt();

    QList<QString> lstName=m_emitter->getAllNameChannel();
    QString s="SELECT * FROM "+nameTable;
    QSqlQuery query(s);

    QProgressDialog progress("Load data...", "Cancel", 0, numTasks, this);
    progress.setWindowModality(Qt::WindowModal);

    int count=0;
    while (query.next()) {
       for(int i=0;i<lstName.size();i++){
           int fieldNo = query.record().indexOf(lstName[i]);
           int fieldDate= query.record().indexOf("datetime");
           QString str = query.value(fieldDate).toString();
           QDateTime dateTime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");//.zzz000

           double value = query.value(fieldNo).toDouble();
           double date= dateTime.toTime_t();
           listCurves [lstName[i]]->add(QCPGraphData(date,value));

       }
       if (progress.wasCanceled())
           break;
       progress.setValue(count);
       count++;

    }
    progress.setValue(numTasks);
}


void MainWindow::updateSplitter(int pos, int index)
{
    for(int i=0;i<m_view.size();i++)
        m_view.at(i).data()->setHeightSplitter(pos);
}

void MainWindow::updateAllData()         // update data TableData and MSCPolarView
{
    QMap<QString,double> map=m_emitter->getAllDataChannel();
    QMapIterator<QString, double> it(map);
    QMap<double,double> mapMSC;
    QMap<double,double> mapColor;

    int row=0;
    int countKey=0;
    m_dataTable->setRowCount(map.size());
    QString sname,svalue;

    while (it.hasNext()) {
        it.next();
        //save to database
        sname=sname+it.key()+",";
        svalue=svalue+QString::number(it.value(),'g',3)+",";

        //view data table
        m_dataTable->setItem(row,0,new QTableWidgetItem(it.key()));
        QString s=QString::number(it.value(),'g',3);
        m_dataTable->setItem(row,1,new QTableWidgetItem(s));

        // add mapMSC
        double tempMaxArm=m_maxArm;
        if(it.key().left(2)=="AM"){
            mapMSC.insert(countKey/tempMaxArm*360.0,it.value());
            mapColor.insert(countKey,it.value());
            countKey++;
        }

        //view dmt view
        if(it.key()=="tension")
           m_dmtview->setTension(it.value());
        if(it.key()=="vol_ac")
           m_dmtview->setVolAc(it.value());
        if(it.key()=="amp_ac")
           m_dmtview->setAmpe(it.value());
        if(it.key()=="depth"){
           m_dmtview->setDepth(it.value());
           qDebug()<<"DEPTH:"<<it.value();
        }
        if(it.key()=="speed")
           m_dmtview->setSpeed(it.value());
       //qDebug()<<it.key()<<"-"<<s;
       row++;
    }

    sname="("+sname+"datetime)";
    svalue=" values("+svalue+"datetime('now','localtime'))";
    //QString sq="INSERT INTO TESTONE"+sname+svalue;
    QString sq="INSERT INTO ["+m_nameDataTable+"]"+sname+svalue;
    //qDebug()<<sq;
    QSqlQuery query;
    query.prepare(sq);
    if(query.exec())
    {
        statusBar()->showMessage("data saving...");

    }
    else
    {
         statusBar()->showMessage("ERROR SAVING DATA:error insert data");

    }

    //UPDATE MSCPolarView
    m_mscpolar->UpdateData(mapMSC);
    //Update MSCColorVIew
   m_msccolor->UpdateData(listCurves);
    //update DMT LCD display
    //m_dmtview->setValue(1324,40,240,2,11);
}

void MainWindow::openArm()
{
    Command *cmdOpenArm=new CommandOpenArmMSC();
    m_emitter->addCommand(cmdOpenArm);
}

void MainWindow::closeArm()
{
    Command *cmdCloseArm=new CommandCloseArmMSC();
    m_emitter->addCommand(cmdCloseArm);
}

void MainWindow::stopArm()
{
    //m_emitter->stop();
    m_emitter->removeLastCommand();
    //m_emitter->start();
}

void MainWindow::createMenu()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //save layout
    QSettings settings("MySoft", "Star Runner");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
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

void MainWindow::setMaxArm(int maxArm)
{
    m_maxArm=maxArm;
}

void MainWindow::createTableDataSQL()
{

}


