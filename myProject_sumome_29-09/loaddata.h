#ifndef LOADDATA_H
#define LOADDATA_H

#include <QDialog>

namespace Ui {
class loaddata;
}

class loaddata : public QDialog
{
    Q_OBJECT

public:
    explicit loaddata(QWidget *parent = nullptr);
    ~loaddata();

private slots:
    void on_btnAdd_clicked();

    void on_btnExit_clicked();

signals:
    void loaddata_sig(QString nameTable);

private:
    Ui::loaddata *ui;
};

#endif // LOADDATA_H
