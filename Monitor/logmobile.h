#ifndef LOGMOBILE_H
#define LOGMOBILE_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

#include <datahandler.h>
#include <logheardbeatwatcher.h>
#include <QGuiApplication>

class LogMobile : public QTcpSocket
{

    Q_OBJECT

public:
    LogMobile();
signals:
    void connectedToServer();

    void loggedInToServer();

    void syncedFromServer(QJsonObject obj);

    void gotVersionFromServer(QString version);

    void loggedOutFromServer();

    void loggedFaild();

    void userDisconnected();
public slots:
    void socketConnected();

    void socketDisconnected();

    void socketError(QAbstractSocket::SocketError err);

    void readyData();

    void handleObject(QJsonObject obj);

    void handleHeardBeatPackage(QByteArray arr);

    QString getUserLoginKey() const;
    void setUserLoginKey(const QString &value);

    QDateTime getUserLastActiveTime() const;
    void setUserLastActiveTime(const QDateTime &value);

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

private:
    Platform platform = Platform::Mobile;

    int userKey = 0;

    QString userLoginKey;

    QDateTime userLastActiveTime;

    QString version = "0.2";

    DataHandler * dh;

    LogHeardBeatWatcher * watcher;

    bool isConnected = false;

    void handleLogin(QJsonObject obj);

    void handleVersion(QJsonObject obj);

    void handleSyncData(QJsonObject obj);

    void handleClientConnected(QJsonObject obj);
};

#endif // LOGMOBILE_H_H
