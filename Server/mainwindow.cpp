#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    server(new LogServer("127.0.0.1",2333,this)),
    dynamicChart(new QChart()),
    m_series(new QLineSeries(dynamicChart)),
    axis_X(new QDateTimeAxis),
    axis_Y(new QValueAxis),
    m_mobile_series(new QLineSeries(dynamicChart)),
    serverThread(new QThread())
{
    ui->setupUi(this);
    connect(server,&LogServer::newServerInformation,this,&MainWindow::handleNewServerInformation);
    connect(serverThread,&QThread::started,server,&LogServer::initializeServer);

    server->moveToThread(serverThread);

    serverThread->start();
    initializeSettings();
}

MainWindow::~MainWindow()
{
    isStop = true;
    delete ui;
}

void MainWindow::refreshUserCount()
{
    while(!isStop)
    {
        qreal x = dynamicChart->plotArea().width() / axis_X->tickCount();
        int desktopCount = server->lstDesktop.count();
        int mobileCount = server->lstMobile.count();
        QDateTime xValue = QDateTime::currentDateTime();
        m_series->append(xValue.toMSecsSinceEpoch(),desktopCount);
        m_mobile_series->append(xValue.toMSecsSinceEpoch(),mobileCount);
        if(xValue >= axis_X->max())
            dynamicChart->scroll(x * 4,0);
        if(desktopCount > axis_Y->max()){
            axis_Y->setRange(0,1.8 * desktopCount);
        }
        else if(mobileCount > axis_Y->max()){
            axis_Y->setRange(0,1.8 * mobileCount);
        }
        else if(desktopCount == 0 && mobileCount == 0){
            axis_Y->setRange(0,20);
        }

        QThread::msleep(chartRefreshDelay);
    }
}

void MainWindow::initializeSettings()
{
    //widget
    this->setWindowTitle(tr("Server"));
    //charts
    QPen orange;
    orange.setColor(QColor("#d35400"));
    orange.setWidth(2);
    m_mobile_series->setPen(orange);

    orange.setColor(QColor("#2980b9"));
    orange.setWidth(2);
    m_series->setPen(orange);

    m_series->setName(tr("Desktop"));
    m_mobile_series->setName(tr("Mobile"));

    dynamicChart->addSeries(m_mobile_series);
    dynamicChart->addSeries(m_series);

    axis_X->setTickCount(10);
    axis_X->setFormat("hh:mm");
    axis_Y->setTickCount(10);

    dynamicChart->addAxis(axis_Y, Qt::AlignLeft);
    dynamicChart->addAxis(axis_X, Qt::AlignBottom);
    m_series->attachAxis(axis_X);
    m_series->attachAxis(axis_Y);

    m_mobile_series->attachAxis(axis_X);
    m_mobile_series->attachAxis(axis_Y);

    dynamicChart->setTitle(tr("All Online-User"));
    dynamicChart->setAnimationOptions(QChart::AllAnimations);

    dynamicChart->axisY()->setRange(0,20);
    dynamicChart->axisX()->setRange(QDateTime(QDate::currentDate(),QTime::currentTime()),QDateTime(QDate::currentDate(),QTime::currentTime().addSecs(30)));


    ui->crtUser->setChart(dynamicChart);
    ui->crtUser->setRenderHint(QPainter::Antialiasing);
    m_series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(),0);
    m_mobile_series->append(QDateTime::currentDateTime().toMSecsSinceEpoch(),0);
    QtConcurrent::run(this,&MainWindow::refreshUserCount);
}

void MainWindow::handleNewServerInformation(Log l)
{
   ui->txtConsole->setText(ui->txtConsole->toPlainText()+"\n" + l.getLogString());
   ui->txtConsole->moveCursor(QTextCursor::End);
}

void MainWindow::on_btnDesktop_clicked()
{
    server->ls->addInformation(tr("The count of desktop user: ") + QString::number(server->lstDesktop.count()));
}

void MainWindow::on_btnMobile_clicked()
{
    server->ls->addInformation(tr("The count of mobile user: ") + QString::number(server->lstMobile.count()));
}

void MainWindow::on_btnSetVersion_clicked()
{
    server->setVersion(QString::number(ui->dblVersion->value()));
}


void MainWindow::on_pushButton_2_clicked()
{
    server->watcher->setFrequency(ui->intQueueDelay->value());
}

void MainWindow::on_pushButton_clicked()
{
    chartRefreshDelay = ui->intChartDelay->value();
}
