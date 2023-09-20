#include "headerwiget.h"
#include "QPainter"

HeaderWiget::HeaderWiget()
{

}

HeaderWiget::HeaderWiget(TableModel *tablemodel)
{
    m_tablemodel=tablemodel;
}

void HeaderWiget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

     QPainter qp(this);
     drawLines(&qp);
}

void HeaderWiget::drawLines(QPainter *qp)
{

    QFont font = qp->font() ;
    /* twice the size than the current font size */
    font.setPointSize(10);
    /* set the modified font to the painter */
    qp->setFont(font);

    for(int i=0;i<m_tablemodel->rowCount();i++){
        //QPen pen(Qt::blue, 1, Qt::SolidLine);
        QString s=m_tablemodel->index(i,6).data().toString();  //6 color
        QColor color;
        color.setNamedColor(s);
        qp->setPen(QPen(color));
        //name
        QString sname=m_tablemodel->index(i,2).data().toString();
        //min max
        double min,max;
        min=m_tablemodel->index(i,3).data().toDouble();
        max=m_tablemodel->index(i,4).data().toDouble();

        qp->drawLine(30, (i+1)*20,this->size().width()-15,(i+1)*20);
        qp->drawText(30,(i+1)*20-2,QString::number(min));
        qp->drawText(this->size().width()-45,(i+1)*20-2,QString::number(max));
        qp->drawText(this->size().width()/2,(i+1)*20-2,sname);
    }
}
