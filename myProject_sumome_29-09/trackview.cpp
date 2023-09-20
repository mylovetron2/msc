#include "trackview.h"

#include <QtWidgets>

TrackView::TrackView(QWidget *parent)
     : QAbstractItemView(parent)
{
    m_CustomPlot=new QCustomPlot;
    //m_Model=new TableModel;
    //m_Model->setTable("curve");
    //m_Model->select();

    layout= new QVBoxLayout();
    setupChart();
    layout->addWidget(m_CustomPlot);
    setLayout(layout);

}

void TrackView::setupChart()
{
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeFormat("h:m");
    double now = QDateTime::currentDateTime().toTime_t();

    m_CustomPlot->yAxis->setTicker(dateTimeTicker);
    m_CustomPlot->yAxis->setRangeReversed(true);
    m_CustomPlot->yAxis->setRange(now, now+1*3600);

    m_CustomPlot->xAxis->setTickLabels(false);
     //m_CustomPlot->xAxis->setRange(200,800);

    m_CustomPlot->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectPlottables);
    m_CustomPlot->axisRect()->setupFullAxesBox();

    /*
    QCPAxisRect *wideAxisRect = new QCPAxisRect(m_CustomPlot);
    QCPAxis *headerAxis=new QCPAxis(wideAxisRect,QCPAxis::atTop);
    QCPAxis *headerAxis2=new QCPAxis(wideAxisRect,QCPAxis::atTop);

    wideAxisRect->setupFullAxesBox(true);
    //wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atTop)->setTickLabelColor(Qt::red); // add an extra axis on the left and color its numbers
    //wideAxisRect->axis(QCPAxis::atTop)->ticker()->setTickCount(20);
    //wideAxisRect->axis(QCPAxis::atTop)->setBasePen(QPen(Qt::red));
    //wideAxisRect->axis(QCPAxis::atTop)->grid()->setVisible(false);

    headerAxis->setBasePen(QPen(Qt::red));
    headerAxis->setOffset(14);
    headerAxis->setTickLabelColor(Qt::red);

    headerAxis2->setBasePen(QPen(Qt::blue));
    headerAxis2->setOffset(15);
    headerAxis2->setTickLabelColor(Qt::blue);

    //QCPMarginGroup *marginGroup = new QCPMarginGroup(m_CustomPlot);
    //wideAxisRect->setMarginGroup(QCP::msTop, marginGroup);


    m_CustomPlot->plotLayout()->addElement(0, 1, wideAxisRect);

    //m_CustomPlot->setRangeZoom(Qt::Horizontal|Qt::Vertical);
    //m_CustomPlot->setRangeDrag(Qt::Horizontal|Qt::Vertical);
    */

    QCPAxis *rang1=new QCPAxis(m_CustomPlot->axisRect(),QCPAxis::atTop);
    rang1->setRangeLower(0);
    rang1->setRangeUpper(1000);
    m_CustomPlot->addGraph(m_CustomPlot->yAxis, m_CustomPlot->xAxis);
    m_CustomPlot->graph(0)->setValueAxis(rang1);

    //QString s=m_Model->index(0,5).data().toString();
    QColor color;
    color.setNamedColor("blue");
    m_CustomPlot->graph(0)->setPen(QPen(color));


    QCPAxis *rang2=new QCPAxis(m_CustomPlot->axisRect(),QCPAxis::atTop);
    rang2->setRangeLower(0);
    rang2->setRangeUpper(500);
    m_CustomPlot->addGraph(m_CustomPlot->yAxis, m_CustomPlot->xAxis);
    m_CustomPlot->graph(1)->setValueAxis(rang2);
    m_CustomPlot->graph(1)->setPen(QPen(Qt::red));

    m_CustomPlot->axisRect()->addAxis(QCPAxis::atTop)->setTickLabelColor(Qt::red);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,1)->setBasePen(QPen(Qt::red));
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,1)->ticker()->setTickCount(1);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,1)->setSubTicks(false);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,1)->setLabel("Mic1");
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,1)->setLabelColor(Qt::red);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,1)->setLabelPadding(-12);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,1)->setTickLabelPadding(0);

    m_CustomPlot->axisRect()->addAxis(QCPAxis::atTop)->setTickLabelColor(Qt::blue);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,2)->setBasePen(QPen(Qt::blue));
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,2)->ticker()->setTickCount(1);
    //m_CustomPlot->axisRect()->axis(QCPAxis::atTop,2)->ticker()->setSub;
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,2)->setLabel("Mic2");
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,2)->setLabelColor(Qt::blue);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,2)->setLabelPadding(-12);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,2)->setTickLabelPadding(0);
    m_CustomPlot->axisRect()->axis(QCPAxis::atTop,2)->setSubTicks(false);

}

void TrackView::paintEvent(QPaintEvent *event)
{
    QModelIndex index;
    index=model()->index(0,1);
    double ccl=model()->data(index).toDouble();
    index=model()->index(0,4);
    double time=model()->data(index).toDouble();
    m_CustomPlot->graph(0)->addData(time,ccl);
    index=model()->index(0,2);
    int arm1=model()->data(index).toInt();
    m_CustomPlot->graph(1)->addData(time,arm1);
    m_CustomPlot->replot();

}

/*
void TrackView::setModel(QAbstractItemModel *model)
{

}
*/
QRect TrackView::visualRect(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QRect();
}

void TrackView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{

}

QModelIndex TrackView::indexAt(const QPoint &point) const
{
    return(QModelIndex());
}

QModelIndex TrackView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    return(QModelIndex());
}


int TrackView::horizontalOffset() const
{
    //return horizontalScrollBar()->value();
    return 0;
}

int TrackView::verticalOffset() const
{
    //return verticalScrollBar()->value();
    return 0;
}

bool TrackView::isIndexHidden(const QModelIndex &index) const
{
    return false;
}

void TrackView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{

}

QRegion TrackView::visualRegionForSelection(const QItemSelection &selection) const
{
     return(QRegion());
}

void TrackView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{


}

void TrackView::updateSettingChar()
{
    //QString s=m_Model->index(0,5).data().toString();
    //QColor color;
    //color.setNamedColor(s);
    //m_CustomPlot->graph(0)->setPen(QPen(color));
    //m_CustomPlot->replot();
}
