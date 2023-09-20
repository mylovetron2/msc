#ifndef DMTVIEW_H
#define DMTVIEW_H

#include <QWidget>
#include <QLCDNumber>

namespace Ui {
class DMTView;
}

class DMTView : public QWidget
{
    Q_OBJECT

public:
    explicit DMTView(QWidget *parent = nullptr);
    ~DMTView();
    void setValue(double depth,double speed,int voltac,int ampe,int tension);
    void setDepth(double depth);
    void setTension(double tension);
    void setVolAc(double vol);
    void setAmpe(double ampe);
    void setSpeed(double speed);
private:
    Ui::DMTView *ui;
};

#endif // DMTVIEW_H
