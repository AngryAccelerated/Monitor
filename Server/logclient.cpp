#include "logclient.h"

LogClient::LogClient(QObject *parent)
{
    this->setParent(parent);
}


QString LogClient::getUserLoginKey() const
{
    return userLoginKey;
}

void LogClient::setUserLoginKey(const QString &value)
{
    userLoginKey = value;
}

QDateTime LogClient::getUserLastActiveTime() const
{
    return userLastActiveTime;
}

void LogClient::setUserLastActiveTime(const QDateTime &value)
{
    userLastActiveTime = value;
}

ClientPlatform LogClient::getUserPlatform() const
{
    return userPlatform;
}

void LogClient::setUserPlatform(const ClientPlatform &value)
{
    userPlatform = value;
}

int LogClient::getUserKey() const
{
    return userKey;
}

void LogClient::setUserKey(int value)
{
    userKey = value;
}

bool LogClient::isSockValid()
{
    return this->socketDescriptor() == -1 ? false : true;
}

void LogClient::sendVersion(QByteArray version)
{
    if(isSockValid())
        this->write(version);
}



