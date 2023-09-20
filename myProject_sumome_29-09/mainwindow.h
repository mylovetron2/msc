#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "emitter.h"
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "curvesetting.h"
#include "trackview.h"
#include "trackviewwidget.h"
#include "QMap"
#include "mscpolarview.h"
#include "msccolorview.h"
#include "loaddata.h"
#include "dmtview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SettingsDialog;
class ParameterDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openPort();
    void startLog();
    void stopLog();
    void openCurveAttributeDialog();
    void createView();
    void loadConfig();
    void saveLayout();
    void loadLayout();
    void setMaxArm(int maxArm);
    void createTableDataSQL();
    void loadData(QString nameTable);

public slots:
    //void on_actionDevice_connect_triggered();
    void test(int pos,int index);
    void getRealData(QByteArray str);
    void updateSplitter(int pos,int index);
    void updateAllData();
    void openArm();
    void closeArm();
    void stopArm();
    void createMenu();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    SettingsDialog *m_settings = nullptr;
    ParameterDialog *m_parameter=nullptr;

    loaddata *m_loaddata=nullptr;
    CurveSetting *m_curveSetting=nullptr;
    Emitter *m_emitter;
    QThread *m_pThread;
    QSqlQueryModel *model;
    QList<QSharedPointer<TrackViewWidget>> m_view;
    //int m_mic1,m_mic2,m_vir1,m_vir2;
    //boolean stateView;
    double m_date;
    QTableWidget *m_dataTable;
    QMap<QString,QSharedPointer< QCPGraphDataContainer >> listCurves;
    MSCPolarView *m_mscpolar;
    MSCColorView *m_msccolor;
    DMTView *m_dmtview;
    int m_maxArm;
    QString m_nameDataTable;
    QDialog *m_ProcessBarDlg;
    QProgressBar *m_progressBar;
    QMenu *m_myMenu;

};
#endif // MAINWINDOW_H
