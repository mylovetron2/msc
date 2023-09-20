#ifndef PARAMETERDIALOG_H
#define PARAMETERDIALOG_H

#include <QDialog>

namespace Ui {
class ParameterDialog;
}

class ParameterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParameterDialog(QWidget *parent = nullptr);
    ~ParameterDialog();

private:
    Ui::ParameterDialog *ui= nullptr;
    double m_fEncoderConst;
};

#endif // PARAMETERDIALOG_H
