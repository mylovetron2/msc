#include "msccolorview.h"

MSCColorView::MSCColorView(QWidget *parent) : QWidget(parent)
{

    m_MaxArm=40;
    m_rowData=1;
    m_intervalView=10; //10 phut
    m_countData=0;
    CreateChart();
}

void MSCColorView::CreateChart()
{

    static QTime timeStart = QTime::currentTime();
    double key = timeStart.msecsTo(QTime::currentTime())/1000.0;
    double now = QDateTime::currentDateTime().toTime_t();

    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("h:m");

    m_CustomPlot=new QCustomPlot(this);
    m_CustomPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    m_CustomPlot->axisRect()->setupFullAxesBox(true);
    m_CustomPlot->xAxis->setLabel(QString::number(m_MaxArm)+" ARM");
    //m_CustomPlot->yAxis->setLabely("");
    m_CustomPlot->yAxis->setTicker(dateTimeTicker);
    m_CustomPlot->yAxis->setRangeReversed(true);
    m_CustomPlot->xAxis->setTickLabels(false);
    //m_CustomPlot->yAxis->setTickLabels(false);

    //m_CustomPlot->yAxis->setRange(now, 1*60, Qt::AlignTop);

    int nx = m_MaxArm*2;
    int ny =1;// m_rowData;
    m_data=new QCPColorMapData(m_MaxArm*2,m_rowData,QCPRange(0,m_MaxArm*2),QCPRange(now,now+3));
    m_graph = new QCPColorMap(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
    m_graph->setData(m_data);
    m_graph->data()->setSize(nx,ny);
    m_data=m_graph->data();
    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(m_CustomPlot);
    m_CustomPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    m_graph->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Color range");
    // set the color gradient of the color map to one of the presets:
    m_graph->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.
    m_graph->setDataRange(QCPRange(0, 1024));
    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    //colorMap->rescaleDataRange();
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_CustomPlot);
    m_CustomPlot->axisRect()->setMarginGroup(QCP::msTop|QCP::msBottom, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    m_CustomPlot->rescaleAxes();
    m_CustomPlot->replot();
    QVBoxLayout *vLayout= new QVBoxLayout();
    vLayout->addWidget(m_CustomPlot);
    setLayout(vLayout);

}

void MSCColorView::UpdateData(QMap<QString, QSharedPointer<QCPGraphDataContainer> > listCurves)
{

    m_data->clearAlpha();
    static QTime timeStart = QTime::currentTime();
    //double key = timeStart.msecsTo(QTime::currentTime())/1000.0;
    double now = QDateTime::currentDateTime().toTime_t();
    m_CustomPlot->yAxis->setRange(now,m_intervalView*60,Qt::AlignRight);

    int nx = m_MaxArm*2;
    int ny = listCurves["AM01"]->size();
    int ystart=0;

    if(ny<=m_intervalView*60){
        m_countData++;
        m_data->setSize(nx,ny);

    }
    else{
        m_data->setSize(nx,m_intervalView*60);
        ystart=ny-m_intervalView*60;
    }
    m_data->setRange(QCPRange(0,m_MaxArm*2),QCPRange(now-m_countData,now));
    int nmap=0;
    for(int i=0;i<nx;i++){
        int ytemp=ystart;
        for(int y=0;y<m_countData;y++){
            if(i%2==0){
                if(i<m_MaxArm/2-2)   //18
                    m_data->setCell(i,y,listCurves["AM0"+QString::number(i/2+1)]->at(ytemp)->value);
                else
                    m_data->setCell(i,y,listCurves["AM"+QString::number(i/2+1)]->at(ytemp)->value);
                 nmap++;

            }
            else{
                m_data->setAlpha(i,y,0);

            }
            ytemp++;
        }
    }

    m_CustomPlot->replot();
}

void MSCColorView::SetMaxArm(int maxArm)
{
    m_MaxArm=maxArm;
}

void MSCColorView::RowData(int rowData)
{
    m_rowData=rowData;
}
