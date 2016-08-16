#include "logdesktop.h"

LogDesktop::LogDesktop(LogSet *client) :
    dh(new DataHandler(this)),
    ls(new LogSet()),
    userKey(0),
    watcher(new LogHeardBeatWatcher),
    clientLs(client),
    reader(new LogReader)
{


    connect(this,&LogDesktop::readyRead,this,&LogDesktop::readyData);
    connect(this,&LogDesktop::disconnected,this,&LogDesktop::socketDisconnected);
    connect(this,&LogDesktop::connectedToServer,this,&LogDesktop::socketConnected);
    connect(dh,&DataHandler::newObject,this,&LogDesktop::handleObject);
    connect(watcher,&LogHeardBeatWatcher::sendHeardBeatPackage,this,&LogDesktop::handleHeardBeatPackage);
    connect(reader,&LogReader::finished,reader,&LogReader::deleteLater);
    connect(watcher,&LogHeardBeatWatcher::finished,watcher,&LogHeardBeatWatcher::deleteLater);
    connect(reader,&LogReader::newInformation,this,&LogDesktop::handleFromRegister);

    connect(this,&LogDesktop::connectedToServer,[=](){
        loginAccount(userLoginKey);
    });
    connect(clientLs,&LogSet::newLog,[=](Log l){
        syncLog(l);
    });
    connect(ls,&LogSet::newLog,[=](Log l){
        qDebug() << l.getLogString();
    });
    connect(this,&LogDesktop::connectedToServer,[=](){
        //watcher->setDataHandler(dh);
        //watcher->start();
        //reader->start();
        ls->addNotice(tr("Connect To Server Successfully."),tr("Connected"),true);
        //this->getVersion();
    });
    connect(this,&LogDesktop::gotVersionFromServer,[=](QString v){
        if(v.toDouble() > version.toDouble()){
            ls->addNotice(tr("The version of server larger than desktop.We will disconnected from server."));
            this->disconnectFromHost();
        }else if(v.toDouble() == version.toDouble()){
            ls->addNotice(tr("Your client version is latest."));
        }
    });



    dh->setParent(this);
    ls->setParent(this);
    if(clientLs != NULL)
        connect(clientLs,SIGNAL(newLog(Log)),this,SLOT(syncLog(Log)));

    this->connectToHost(QString("127.0.0.1"),2333);

}

void LogDesktop::socketConnected()
{
    setIsConnected(true);
    ls->addNotice(tr("Socket connected!"),tr("CONNECTED"));
}

void LogDesktop::socketDisconnected()
{
    ls->addNotice(tr("Socket disconnected!"),tr("DISCONNECTED"));
    watcher->wait();
    if(isConnected)
        emit disconnectedFromServer();
    emit loggedOutFromServer();
}

void LogDesktop::socketError(QAbstractSocket::SocketError err)
{
    ls->addError(this->errorString(),tr("SOCKETERROR"),false);
}

void LogDesktop::readyData()
{
    dh->handleData(this->readAll());
}

bool LogDesktop::getIsConnected() const
{
    return isConnected;
}

void LogDesktop::setIsConnected(bool value)
{
    isConnected = value;
}

void LogDesktop::handleObject(QJsonObject obj)
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

int LogDesktop::getUserKey() const
{
    return userKey;
}

void LogDesktop::setUserKey(int value)
{
    userKey = value;
}

void LogDesktop::logout()
{
    if(this->socketDescriptor() != -1 && userKey > 10)
    {
        QVariantMap map;
        map["dataCommand"] = (int)DataCommand::Logout;
        this->write(dh->buildData(map).toUtf8());
    }
}

void LogDesktop::handleLogin(QJsonObject obj)
{
    bool b = obj.value("dataResult").toBool();
    ls->addInformation(tr("Login result is: ") + QString::number(b));
    if(b)
    {
        userKey = obj.value("dataString").toInt();
        ls->addInformation(tr("get userkey is: ") + QString::number(userKey));
        emit loggedInToServer();
    }
    else
        ls->addError(tr("cannot login!"),tr("LOGIN"),false);
}

void LogDesktop::handleVersion(QJsonObject obj)
{
    ls->addInformation(tr("client lastest version is: ") + obj.value("dataString").toString());
    emit gotVersionFromServer(obj.value("dataString").toString());
}

void LogDesktop::handleSyncData(QJsonObject obj)
{
    if(obj.value("dataResult").toBool())
        ls->addInformation(tr("sync data successfully"),tr("SYNC"),true);
    emit syncedToServer();
}

void LogDesktop::handleClientConnected(QJsonObject obj)
{
}

void LogDesktop::loginAccount(const QString & id)
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

void LogDesktop::syncLog(Log lg)
{
    if(this->socketDescriptor() != -1 && userKey > 0)
    {
        QVariantMap map;
        map["dataNote"] = lg.getNote();
        map["dataString"] = lg.getText();
        map["dataType"] = (int)lg.getType();
        map["dataResult"] = lg.getReturnValue();
        map["dataTime"] = lg.getDateTimeString();
        map["dataCommand"] = (int)DataCommand::SyncData;
        map["dataUserKey"] = getUserKey();
        this->write(dh->buildData(map).toUtf8());
    }
}

void LogDesktop::syncLog(LogSet *logSet)
{
    foreach (Log log, logSet->lstLog)
        syncLog(log);
}

void LogDesktop::handleHeardBeatPackage(QByteArray arr)
{
    if(this->socketDescriptor() != -1)
        this->write(arr);
    else
        ls->addError(tr("Can't send heardbeat package"),tr("HEARDBEAT"),false);
}

void LogDesktop::handleFromRegister(int type, QString text, QString note, bool result)
{
    switch (type) {
    case (int)LogType::Error:
        clientLs->addError(text, note, result);
        break;
    case (int)LogType::Information:
        clientLs->addInformation(text, note, result);
        break;
    case (int)LogType::Notice:
        clientLs->addNotice(text, note, result);
        break;
    case (int)LogType::Verbose:
        clientLs->addVerbose(text, note, result);
        break;
    case (int)LogType::Warning:
        clientLs->addWarning(text, note, result);
        break;
    }
}

Platform LogDesktop::getPlatform() const
{
    return platform;
}

void LogDesktop::setPlatform(const Platform &value)
{
    platform = value;
}

void LogDesktop::getVersion()
{
    if(this->socketDescriptor() != -1 && isConnected)
    {
        QVariantMap map;
        map["dataTime"] = getCurrentTimeString();
        map["dataCommand"] = (int)DataCommand::Version;
        this->write(dh->buildData(map).toUtf8());
    }
}

QString LogDesktop::getCurrentTimeString() const
{
    return QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
}
//getters and setters

LogSet *LogDesktop::getLs() const
{
    return ls;
}

QString LogDesktop::getUserLoginKey() const
{
    return userLoginKey;
}

void LogDesktop::setUserLoginKey(const QString &value)
{
    userLoginKey = value;
}

QDateTime LogDesktop::getUserLastActiveTime() const
{
    return userLastActiveTime;
}

void LogDesktop::setUserLastActiveTime(const QDateTime &value)
{
    userLastActiveTime = value;
}

LogSet *LogDesktop::getClientLs() const
{
    return clientLs;
}

void LogDesktop::setClientLs(LogSet *value)
{
    clientLs = value;
}



