#ifndef LOGSERVER_H
#define LOGSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>


#include <datahandler.h>
#include <logset.h>
#include <logclient.h>
#include <logclientlifewatcher.h>
using namespace QtConcurrent;

class LogServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit LogServer(const QString & ip, const int & port,QObject * parent = 0);
    ~LogServer();
    void setVersion(const QString &value);



    LogSet *ls;

    DataHandler * dh;

    QSqlDatabase db;

    QString version = "0.2";

    QList<LogClient*> lstDesktop;

    QList<LogClient*> lstMobile;


    QString getTypeName(int a);

    QString getVersion() const;

    QByteArray createVersion();

    QByteArray createConnectedData();

    QString getCurrentTimeString() const;

    LogClientLifeWatcher * watcher;
public slots:
    void handleConnection();

    void handleObject(LogClient *l, QJsonObject obj);

    void socketNewData();

    void handleError(QAbstractSocket::SocketError err);

    void handleDisconnect();

    void initializeServer();

signals:

    void newClientConnection();

    void newServerInformation(Log l);

    void newVersion(QByteArray v);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QString addr;
    int addr_port;


    void checkClientLife();

    void createLogTable(const QString &name);

    bool checkAccountKey(const QJsonObject & obj);

    void handleLogin(LogClient * lc, QJsonObject obj);

    void handleLogout(LogClient * lc,QJsonObject obj);

    void handleVersion(LogClient * lc,QJsonObject obj);

    void handleSyncData(LogClient * lc,QJsonObject obj);

    void handleHeardBeat(LogClient * lc);

    void handleClientConnected(LogClient * lc);

    void handleDesktopClientConnected(LogClient * lc);

    void handleMobileClientConnected(LogClient *lc);

    bool addLogIntoDatabase(const QString &name, const QJsonObject &obj);

};

#endif // LOGSERVER_H
