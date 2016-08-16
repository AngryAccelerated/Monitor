#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QtConcurrent/QtConcurrent>

#include <logserver.h>
using namespace QtConcurrent;
using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void handleNewServerInformation(Log l);
    void refreshUserCount();
private slots:
    void on_btnDesktop_clicked();

    void on_btnMobile_clicked();

    void on_btnSetVersion_clicked();


    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    LogServer * server;
    QChart * dynamicChart;
    QDateTimeAxis * axis_X;
    QLineSeries * m_series;
    QValueAxis * axis_Y;
    QLineSeries * m_mobile_series;
    QThread * serverThread;
    int chartRefreshDelay = 1000;
    bool isStop = false;
    void initializeSettings();
};

#endif // MAINWINDOW_H
