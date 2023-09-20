#include "trackviewwidget.h"
#include <QSqlQuery>

TrackViewWidget::TrackViewWidget(QWidget *parent) : QWidget(parent)
{
    m_curveAttribute=new TableModel;
    m_curveAttribute->setTable("curve");
    m_curveAttribute->select();

     m_CustomPlot=new QCustomPlot;

     setupChart();

     QVBoxLayout *layout= new QVBoxLayout();
     layout->addWidget(m_CustomPlot);
     setLayout(layout);



}

TrackViewWidget::TrackViewWidget(int id, QString name)
{

    m_viewID=id;
    m_stateView=true;

    m_curveAttribute=new TableModel;
    m_curveAttribute->setTable("curve");
    //m_curveAttribute->setFilter("trackview_id="+QString::number(id));
    m_curveAttribute->select();

     m_CustomPlot=new QCustomPlot;

     setupChart();
     QVBoxLayout *layout= new QVBoxLayout();
     layout->addWidget(m_CustomPlot);
     setLayout(layout);



}



void TrackViewWidget::setupChart()
{

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("h:m");
    double now = QDateTime::currentDateTime().toTime_t();

    m_CustomPlot->yAxis->setTicker(dateTimeTicker);
    m_CustomPlot->yAxis->setRangeReversed(true);
    //m_CustomPlot->yAxis->setRange(now, 2*60, Qt::AlignRight);
    m_CustomPlot->yAxis->setRange(now, 2*60);
    m_CustomPlot->xAxis->setTickLabels(true);
    m_CustomPlot->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectPlottables);
    m_CustomPlot->axisRect()->setupFullAxesBox();

    //m_curveAttribute->index(0,5).data().toString();
    for(int i=0;i<m_curveAttribute->rowCount();i++)
    {
        m_CustomPlot->addGraph(m_CustomPlot->yAxis, m_CustomPlot->xAxis);       //ADD GRAPH

        QCPAxis *rang1=new QCPAxis(m_CustomPlot->axisRect(),QCPAxis::atTop);
        double min,max;
        min=m_curveAttribute->index(i,2).data().toDouble();
        max=m_curveAttribute->index(i,3).data().toDouble();
        rang1->setRange(min,max);
        rang1->setTicks(false);
        m_CustomPlot->graph(i)->setValueAxis(rang1);

        QString s=m_curveAttribute->index(i,5).data().toString();
        QColor color;
        color.setNamedColor(s);
        m_CustomPlot->graph(i)->setPen(QPen(color));
        m_CustomPlot->axisRect()->addAxis(QCPAxis::atTop)->setTickLabelColor(color);  // ADD AXIS
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setBasePen(QPen(color));

        QSharedPointer<QCPAxisTickerText> tickerText(new QCPAxisTickerText);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setTicker(tickerText);
        tickerText->addTick(min,QString::number(min));
        tickerText->addTick(max,QString::number(max));

        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setRange(min,max);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setSubTicks(false);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setLabel(m_curveAttribute->index(i,1).data().toString());
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setLabelColor(color);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setLabelPadding(-12);  //-12
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setTickLabelPadding(0);  //0

    }

    for(int i=0;i<200;i++){
    QColor color(i);

    QCPAxis *rang1=new QCPAxis(m_CustomPlot->axisRect(),QCPAxis::atTop);
    rang1->setRange(0,200);
    rang1->setTicks(false);

    m_CustomPlot->addGraph(m_CustomPlot->yAxis, m_CustomPlot->xAxis);       //ADD GRAPH
      m_CustomPlot->graph(i+3)->setPen(QPen(color));
      m_CustomPlot->graph(i+3)->setVisible(false);
    m_CustomPlot->graph(i+3)->setValueAxis(rang1);

}
    dataContainer = QSharedPointer<QCPGraphDataContainer>(new QCPGraphDataContainer);
    //dataContainer=m_CustomPlot->graph(0)->data();
    m_CustomPlot->graph(1)->setData(dataContainer);
    m_CustomPlot->graph(0)->setData(dataContainer);
    //dataContainer->clear();

    m_CustomPlot->replot();

}

void TrackViewWidget::updateChart()
{


}

void TrackViewWidget::updateCurveAttribute()
{
    m_curveAttribute->select();
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("h:m");
    double now = QDateTime::currentDateTime().toTime_t();

    m_CustomPlot->yAxis->setTicker(dateTimeTicker);
    m_CustomPlot->yAxis->setRangeReversed(true);
    m_CustomPlot->yAxis->setRange(now, 2*60, Qt::AlignRight);
    m_CustomPlot->xAxis->setTickLabels(true);
    m_CustomPlot->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectPlottables);
    m_CustomPlot->axisRect()->setupFullAxesBox();

    //m_curveAttribute->index(0,5).data().toString();
    for(int i=0;i<m_curveAttribute->rowCount();i++)
    {
        QCPAxis *rang1=new QCPAxis(m_CustomPlot->axisRect(),QCPAxis::atTop);
        double min,max;
        min=m_curveAttribute->index(i,2).data().toDouble();
        max=m_curveAttribute->index(i,3).data().toDouble();
        rang1->setRange(min,max);
        rang1->setTicks(false);
        m_CustomPlot->graph(i)->setValueAxis(rang1);

        QString s=m_curveAttribute->index(i,5).data().toString();
        QColor color;
        color.setNamedColor(s);
        m_CustomPlot->graph(i)->setPen(QPen(color));
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setTickLabelColor(color);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setBasePen(QPen(color));

        QSharedPointer<QCPAxisTickerText> tickerText(new QCPAxisTickerText);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setTicker(tickerText);
        tickerText->addTick(min,QString::number(min));
        tickerText->addTick(max,QString::number(max));

        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setRange(min,max);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setSubTicks(false);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setLabel(m_curveAttribute->index(i,1).data().toString());
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setLabelColor(color);
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setLabelPadding(-12);  //-12
        m_CustomPlot->axisRect()->axis(QCPAxis::atTop,i+1)->setTickLabelPadding(0);  //0


    }
    m_CustomPlot->replot();

}

void TrackViewWidget::updateDataChart()
{
    QSqlQuery query("SELECT * FROM data ORDER BY ID DESC LIMIT 1");
       while (query.next()) {
           QString country = query.value(0).toString();
           //doSomething(country);
       }

}

void TrackViewWidget::addDataChart(double date,int mic1,int mic2)
{
    //m_CustomPlot->graph(0)->addData(date,mic1);
    //m_CustomPlot->graph(1)->addData(date,mic2);

    for(int i=0;i<200;i++){
        double temp=QRandomGenerator::global()->bounded(0,200);
        m_CustomPlot->graph(i+3)->addData(date,temp);

    }

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("h:m");
    double now = QDateTime::currentDateTime().toTime_t();

    if(m_stateView==true)
        m_CustomPlot->yAxis->setRange(now, 10*60, Qt::AlignCenter);

    //dataContainer->clear();
    dataContainer->add(QCPGraphData(date,mic2));


   m_CustomPlot->replot();

}

void TrackViewWidget::setStateView(boolean state)
{
    m_stateView=state;
}
