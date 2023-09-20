#include "mscpolarview.h"
#include "QVector"

MSCPolarView::MSCPolarView(QWidget *parent) : QWidget(parent),
    btnOpenArm(new QPushButton("OpenArm")),
    btnCloseArm(new QPushButton("CloseArm")),
    btnStopArm(new QPushButton("StopArm"))
{
    m_CustomPlot=new QCustomPlot(this);
    m_MaxArm=40;
    m_stateArm=0;
    CreateChart();

    connect(this->btnOpenArm,&QPushButton::clicked,
            this, &MSCPolarView::openArm);

    connect(this->btnCloseArm,&QPushButton::clicked,
            this, &MSCPolarView::closeArm);
    connect(this->btnStopArm,&QPushButton::clicked,
            this, &MSCPolarView::stopArm);
}

MSCPolarView::MSCPolarView(int maxArm)
{
    m_CustomPlot=new QCustomPlot(this);
    m_MaxArm=maxArm;
    m_stateArm=0;
    CreateChart();

    connect(this->btnOpenArm,&QPushButton::clicked,
            this, &MSCPolarView::openArm);
    connect(this->btnCloseArm,&QPushButton::clicked,
            this, &MSCPolarView::closeArm);
    connect(this->btnStopArm,&QPushButton::clicked,
            this, &MSCPolarView::stopArm);
}

void MSCPolarView::CreateChart()
{

    m_CustomPlot->plotLayout()->clear();

    QCPPolarAxisAngular *angularAxis = new QCPPolarAxisAngular(m_CustomPlot);
    m_CustomPlot->plotLayout()->addElement(0, 0, angularAxis);
    m_CustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    angularAxis->setRangeDrag(false);
    angularAxis->setTickLabelMode(QCPPolarAxisAngular::lmUpright);
    angularAxis->radialAxis()->setTickLabelMode(QCPPolarAxisRadial::lmUpright);
    angularAxis->radialAxis()->setTickLabelRotation(0);
    angularAxis->radialAxis()->setAngle(90);
    angularAxis->grid()->setAngularPen(QPen(QColor(200, 200, 200), 0, Qt::SolidLine));
    angularAxis->grid()->setSubGridType(QCPPolarGrid::gtAll);

    QCPPolarGraph *g1 = new QCPPolarGraph(angularAxis, angularAxis->radialAxis());
    m_graph = new QCPPolarGraph(angularAxis, angularAxis->radialAxis());
    m_graph->setPen(QPen(QColor(255, 150, 20)));
    m_graph->setBrush(QColor(255, 150, 20, 50));
    //m_graph->setScatterStyle(QCPScatterStyle::ssDiamond);

    double temp=m_MaxArm;
    QVector<double> vectorKey;
    QVector<double> vectorValue;

    for(int i=0;i<m_MaxArm;i++){
        vectorKey.append(i/temp*360.0);
        vectorValue.append(1024);
    }
    m_graph->setData(vectorKey, vectorValue,1);

    angularAxis->setRange(0, 360);
    angularAxis->radialAxis()->setRange(-600, 1024);
    m_CustomPlot->replot();

    QVBoxLayout *vLayout= new QVBoxLayout();
    QHBoxLayout *hLayout= new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(btnOpenArm);
    hLayout->addWidget(btnStopArm);
    hLayout->addWidget(btnCloseArm);

    vLayout->addWidget(m_CustomPlot);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);

}

void MSCPolarView::UpdateData(QMap<double, double> map)
{
    QVector<double> vectorKey;
    QVector<double> vectorValue;
    vectorKey=map.keys().toVector();
    vectorValue=map.values().toVector();
    m_graph->setData(vectorKey, vectorValue,1);
    m_CustomPlot->replot();
}

void MSCPolarView::SetMaxArm(int maxArm)
{
    m_MaxArm=maxArm;
}

void MSCPolarView::openArm()
{
   emit openArm_sig();//open
   btnCloseArm->setEnabled(false);
   btnStopArm->setEnabled(true);
   btnOpenArm->setEnabled(false);
}

void MSCPolarView::closeArm()
{
   emit closeArm_sig();//close
   btnOpenArm->setEnabled(false);
   btnStopArm->setEnabled(true);
   btnCloseArm->setEnabled(false);

}

void MSCPolarView::stopArm()
{
    emit stopArm_sig();//close
    btnCloseArm->setEnabled(true);
    btnStopArm->setEnabled(false);
    btnOpenArm->setEnabled(true);
}
