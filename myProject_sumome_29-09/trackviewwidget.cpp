#include "trackviewwidget.h"
#include <QSqlQuery>

TrackViewWidget::TrackViewWidget(QWidget *parent) : QWidget(parent)
{

}

TrackViewWidget::TrackViewWidget(int id, QString name,QMap<QString,QSharedPointer< QCPGraphDataContainer >> listCurves) :
    btnCurverAttribute(new QPushButton("curve")),
    btnStateView(new QPushButton("pause")),
    m_curveAttributeDialog(new CurveAttribute(id))

{

    m_viewID=id;
    m_stateView=true;
    m_listCurves=listCurves;
    m_CustomPlot=new QCustomPlot;
    m_splitter=new QSplitter;

    updateCurveAttribute();

    m_header=new HeaderWiget(m_curveAttributeDialog->tablemodel);  // tablemodel la bang curve
    m_header->setMinimumHeight(50);
    m_header->setAutoFillBackground(true);
    QPalette p =m_header->palette();
    p.setColor(m_header->backgroundRole(),Qt::white);
    m_header->setPalette(p);
    m_splitter->addWidget(m_header);
    m_splitter->addWidget(m_CustomPlot);
    m_splitter->setOrientation(Qt::Vertical);

    QVBoxLayout *vLayout= new QVBoxLayout();
    QHBoxLayout *hLayout= new QHBoxLayout();
    vLayout->addWidget(m_splitter);
    hLayout->addStretch();
    hLayout->addWidget(btnCurverAttribute);
    hLayout->addWidget(btnStateView);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);

    connect(btnStateView,&QPushButton::clicked,this,&TrackViewWidget::btnStateView_click);
    connect(btnCurverAttribute,&QPushButton::clicked,this,&TrackViewWidget::btnCurveAttribute_click);
    connect(m_curveAttributeDialog->newButton,&QPushButton::clicked,this,&TrackViewWidget::updateCurveAttribute);
    connect(m_splitter, &QSplitter::splitterMoved, this, &TrackViewWidget::getPositionSplit);

}

void TrackViewWidget::getPositionSplit(int pos, int index){
    emit moveSplitter(pos,index);
}

void TrackViewWidget::setHeightSplitter(int height)
{
    m_splitter->setSizes(QList<int>()<<height<<m_splitter->sizes().at(1));

}

int TrackViewWidget::getSizeSplitter()
{
    return m_splitter->sizes().at(1);
}

void TrackViewWidget::setTextBtnStateView(QString name)
{
    btnStateView->setText(name);
}

void TrackViewWidget::updateChart()
{
    //QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    //dateTimeTicker->setDateTimeFormat("h:m");
    double now = QDateTime::currentDateTime().toTime_t();

    if(m_stateView==true)
        m_CustomPlot->yAxis->setRange(now, 10*60, Qt::AlignCenter);

    m_CustomPlot->replot();


}

void TrackViewWidget::updateCurveAttribute()
{
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("h:m");
    double now = QDateTime::currentDateTime().toTime_t();

    m_CustomPlot->yAxis->setTicker(dateTimeTicker);
    m_CustomPlot->yAxis->setRangeReversed(true);
    m_CustomPlot->yAxis->setRange(now, 2*60);
    m_CustomPlot->xAxis->setTickLabels(true);
    m_CustomPlot->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectPlottables);
    m_CustomPlot->axisRect()->setupFullAxesBox();

    int countGrap=0;
    for(int i=0;i<m_curveAttributeDialog->tablemodel->rowCount();i++)
    {
 //--
        QString sname=m_curveAttributeDialog->tablemodel->index(i,2).data().toString();
        if(m_listCurves.contains(sname))
        {

            m_CustomPlot->addGraph(m_CustomPlot->yAxis, m_CustomPlot->xAxis);       //ADD GRAPH

            m_CustomPlot->graph(countGrap)->setData(m_listCurves[sname]);
            QCPAxis *rang1=new QCPAxis(m_CustomPlot->axisRect(),QCPAxis::atTop);
            double min,max;

            min=m_curveAttributeDialog->tablemodel->index(i,3).data().toDouble();
            max=m_curveAttributeDialog->tablemodel->index(i,4).data().toDouble();

            rang1->setRange(min,max);
            rang1->setTicks(false);

            m_CustomPlot->graph(countGrap)->setValueAxis(rang1);

            QString s=m_curveAttributeDialog->tablemodel->index(i,6).data().toString(); // 6 color
            QColor color;
            color.setNamedColor(s);
            m_CustomPlot->graph(countGrap)->setPen(QPen(color));
            countGrap++;
        }
//--
    }

    m_CustomPlot->replot();

}


void TrackViewWidget::setStateView(boolean state)
{
    m_stateView=state;
}


void TrackViewWidget::setData(int indexGraph,QSharedPointer<QCPGraphDataContainer> container)
{
    m_CustomPlot->graph(indexGraph)->setData(container);
}

void TrackViewWidget::btnStateView_click()
{
    m_stateView=!m_stateView;
    if(m_stateView)
        btnStateView->setText("pause");
    else
        btnStateView->setText("play");
}

void TrackViewWidget::btnCurveAttribute_click()
{
    m_curveAttributeDialog->show();
}
