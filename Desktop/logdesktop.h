#ifndef LOGDESKTOP_H
#define LOGDESKTOP_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QRegularExpression>

#include <datahandler.h>
#include <logset.h>
#include <logheardbeatwatcher.h>
#include <logreader.h>

class LogDesktop : public QTcpSocket
{

    Q_OBJECT

public:
    LogDesktop(LogSet * client=0);


    QString getUserLoginKey() const;
    void setUserLoginKey(const QString &value);

    QDateTime getUserLastActiveTime() const;
    void setUserLastActiveTime(const QDateTime &value);

    LogSet *getClientLs() const;
    void setClientLs(LogSet *value);

    LogSet *getLs() const;

    void getVersion();

    QString getCurrentTimeString() const;

    bool getIsConnected() const;
    void setIsConnected(bool value);

    int getUserKey() const;
    void setUserKey(int value);

    void logout();

    Platform getPlatform() const;
    void setPlatform(const Platform &value);

    void loginAccount(const QString &id);
signals:
    void connectedToServer();

    void loggedInToServer();

    void syncedToServer();

    void gotVersionFromServer(QString v);

    void loggedOutFromServer();

    void disconnectedFromServer();
public slots:
    void socketConnected();

    void socketDisconnected();

    void socketError(QAbstractSocket::SocketError err);

    void readyData();

    void handleObject(QJsonObject obj);

    void syncLog(Log lg);

    void syncLog(LogSet * logSet);

    void handleHeardBeatPackage(QByteArray arr);

    void handleFromRegister(int type,QString text,QString note,bool result);
private:
    Platform platform = Platform::Desktop;

    int userKey = 0;

    QString userLoginKey;

    QDateTime userLastActiveTime;

    QString version = "0.2";

    DataHandler * dh;

    LogSet * ls;

    LogSet * clientLs = NULL;

    LogReader * reader;

    LogHeardBeatWatcher * watcher;

    bool isConnected = false;

    void handleLogin(QJsonObject obj);

    void handleVersion(QJsonObject obj);

    void handleSyncData(QJsonObject obj);

    void handleClientConnected(QJsonObject obj);

};

#endif // LOGDESKTOP_H
