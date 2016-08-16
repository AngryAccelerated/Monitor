#include "logmobile.h"



LogMobile::LogMobile() :
    dh(new DataHandler()),
    userKey(0),
    watcher(new LogHeardBeatWatcher)
{

    connect(this,&LogMobile::readyRead,this,&LogMobile::readyData);
    connect(this,&LogMobile::disconnected,this,&LogMobile::socketDisconnected);
    connect(this,&LogMobile::connectedToServer,this,&LogMobile::socketConnected);
    connect(dh,&DataHandler::newObject,this,&LogMobile::handleObject);
    connect(watcher,&LogHeardBeatWatcher::sendHeardBeatPackage,this,&LogMobile::handleHeardBeatPackage);

    connect(this,&LogMobile::gotVersionFromServer,[=](QString v){

    });

    dh->setParent(this);
    watcher->setParent(this);
    watcher->setDataHandler(dh);
    watcher->start();

    connectToHost(QString("127.0.0.1"),2333);
}

void LogMobile::socketConnected()
{
    setIsConnected(true);
}

void LogMobile::socketDisconnected()
{
    if(isConnected){
        isConnected = false;
        emit userDisconnected();
    }
    watcher->wait();
    emit loggedOutFromServer();
}

void LogMobile::socketError(QAbstractSocket::SocketError err)
{
    qDebug() << this->errorString();
}

void LogMobile::readyData()
{
    dh->handleData(this->readAll());
}

bool LogMobile::getIsConnected() const
{
    return isConnected;
}

void LogMobile::setIsConnected(bool value)
{
    isConnected = value;
}

void LogMobile::handleObject(QJsonObject obj)
{
    switch (obj.value("dataCommand").toInt()) {
    case (int)DataCommand::Login:
        handleLogin(obj);
        break;
    case (int)DataCommand::SyncData:
        handleSyncData(obj);
        break;
    case (int)DataCommand::Version:
        handleVersion(obj);
        break;
    case (int)DataCommand::Connected:
        emit connectedToServer();
        break;
    case (int)DataCommand::ClientConnected:
        handleClientConnected(obj);
        break;
    }
}

int LogMobile::getUserKey() const
{
    return userKey;
}

void LogMobile::setUserKey(int value)
{
    userKey = value;
}

void LogMobile::logout()
{
    if(this->socketDescriptor() != -1 && userKey > 10)
    {
        QVariantMap map;
        map["dataCommand"] = (int)DataCommand::Logout;
        this->write(dh->buildData(map).toUtf8());
    }
}

void LogMobile::handleLogin(QJsonObject obj)
{
    bool b = obj.value("dataResult").toBool();
    if(b){
        emit loggedInToServer();
        userKey = obj.value("dataString").toInt();
    }
    else
        emit loggedFaild();
}

void LogMobile::handleVersion(QJsonObject obj)
{
    emit gotVersionFromServer(obj.value("dataString").toString());
}

void LogMobile::handleSyncData(QJsonObject obj)
{
    QJsonObject ch,info;
    ch["type"] = obj["dataType"];
    ch["time"] = obj["dataTime"];
    ch["context"] = obj["dataString"];
    ch["result"] = obj["dataResult"];
    ch["senderKey"] = obj["dataUserKey"];
    ch["note"] = obj["dataNote"];
    info["info"] = ch;
    emit syncedFromServer(info);
}

void LogMobile::handleClientConnected(QJsonObject obj)
{
    if(obj.value("dataResult").toBool())
        qDebug() << "a desktop client is connected: " << obj.value("dataString").toInt();
}

void LogMobile::loginAccount(const QString & id)
{
    if(this->socketDescriptor() != -1 && isConnected)
    {
        QVariantMap map;
        map["dataPlatform"] = (int)platform;
        map["dataString"] = id;
        map["dataTime"] = getCurrentTimeString();
        map["dataCommand"] = (int)DataCommand::Login;
        this->write(dh->buildData(map).toUtf8());
    }
}

void LogMobile::handleHeardBeatPackage(QByteArray arr)
{
    if(this->socketDescriptor() != -1)
        this->write(arr);
    else
        qDebug() << "can't send heardbeat package.";
}

Platform LogMobile::getPlatform() const
{
    return platform;
}

void LogMobile::setPlatform(const Platform &value)
{
    platform = value;
}

void LogMobile::getVersion()
{
    if(this->socketDescriptor() != -1 && isConnected)
    {
        QVariantMap map;
        map["dataTime"] = getCurrentTimeString();
        map["dataCommand"] = (int)DataCommand::Version;
        this->write(dh->buildData(map).toUtf8());
    }
}

QString LogMobile::getCurrentTimeString() const
{
    return QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
}


QString LogMobile::getUserLoginKey() const
{
    return userLoginKey;
}

void LogMobile::setUserLoginKey(const QString &value)
{
    userLoginKey = value;
}

QDateTime LogMobile::getUserLastActiveTime() const
{
    return userLastActiveTime;
}

void LogMobile::setUserLastActiveTime(const QDateTime &value)
{
    userLastActiveTime = value;
}






