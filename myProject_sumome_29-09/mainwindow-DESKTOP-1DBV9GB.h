#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "emitter.h"
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "curvesetting.h"
#include "trackview.h"
#include "trackviewwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SettingsDialog;

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
    void setStateView();

public slots:
    //void on_actionDevice_connect_triggered();
    void test();
    void getRealData(QByteArray str);


private:
    Ui::MainWindow *ui;
    SettingsDialog *m_settings = nullptr;
    CurveSetting *m_curveSetting=nullptr;
    Emitter *m_emitter;
    QThread *m_pThread;
    QSqlQueryModel *model;
    TrackViewWidget *m_view1;
    TrackViewWidget *m_view2;
    //QList<TrackViewWidget*> m_view;
    QList<QSharedPointer<TrackViewWidget>> m_view;
    int m_mic1,m_mic2,m_vir1,m_vir2;
    boolean stateView;
    double m_date;
    //QSharedPointer<QCPGraphDataContainer> dataContainer;
};
#endif // MAINWINDOW_H
