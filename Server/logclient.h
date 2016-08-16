#ifndef LOGCLIENT_H
#define LOGCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDateTime>

enum class ClientPlatform{
    Desktop,
    Mobile
};

class LogClient : public QTcpSocket
{

public:
    LogClient(QObject * parent = 0);


    QString getUserLoginKey() const;
    void setUserLoginKey(const QString &value);

    QDateTime getUserLastActiveTime() const;
    void setUserLastActiveTime(const QDateTime &value);

    ClientPlatform getUserPlatform() const;
    void setUserPlatform(const ClientPlatform &value);

    int getUserKey() const;
    void setUserKey(int value);

    bool isSockValid();

    void sendVersion(QByteArray version);
private:

    int userKey=0;

    QString userLoginKey;

    QDateTime userLastActiveTime;

    ClientPlatform userPlatform;
};

#endif // LOGCLIENT_H
