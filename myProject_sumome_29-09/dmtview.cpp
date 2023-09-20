#include "dmtview.h"
#include "ui_dmtview.h"

DMTView::DMTView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DMTView)
{
    ui->setupUi(this);
    QLCDNumber number;
    ui->lcdDepth->setStyleSheet("color: red;font-weight: bold;");
    //ui->lcdDepth->setSmallDecimalPoint(2);
    ui->lcdSpeed->setStyleSheet("color: red");
    //ui->lcdSpeed->setSmallDecimalPoint(2);
    ui->lcdVoltAc->setStyleSheet("color: red");
    ui->lcdAmpe->setStyleSheet("color: red;font: 75 28pt 'Times New Roman'");
    ui->lcdTension->setStyleSheet("color: red");

}

DMTView::~DMTView()
{
    delete ui;
}

void DMTView::setValue(double depth, double speed, int voltac, int ampe, int tension)
{
    ui->lcdDepth->display(depth);
    ui->lcdSpeed->display(speed);
    ui->lcdVoltAc->display(voltac);
    ui->lcdTension->display(tension);
    ui->lcdAmpe->display(ampe);
}

void DMTView::setDepth(double depth)
{
    ui->lcdDepth->display(depth);
}

void DMTView::setTension(double tension)
{
    ui->lcdTension->display(tension);
}

void DMTView::setVolAc(double vol)
{
    ui->lcdVoltAc->display(vol);
}

void DMTView::setAmpe(double ampe)
{
    ui->lcdAmpe->display(ampe);

}

void DMTView::setSpeed(double speed)
{
     ui->lcdSpeed->display(speed);
}
