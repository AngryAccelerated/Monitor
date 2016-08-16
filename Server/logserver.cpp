#include "logserver.h"
LogServer::LogServer(const QString &ip, const int &port, QObject *parent) :
    ls(new LogSet(this)),
    dh(new DataHandler(this)),
    watcher(new LogClientLifeWatcher(this)),
    addr(ip),
    addr_port(port)
{
    connect(ls,SIGNAL(newLog(Log)),SIGNAL(newServerInformation(Log)));

    connect(this,&LogServer::newClientConnection,this,&LogServer::handleConnection);
    connect(dh,&DataHandler::newObject,this,&LogServer::handleObject);
}

LogServer::~LogServer()
{

}

bool LogServer::checkAccountKey(const QJsonObject & obj)
{
    bool a = true;
    for(int i=0;i<lstMobile.count();++i)
    {
        if(lstMobile.at(i)->getUserLoginKey() == obj.value("dataString").toString())
        {
            ls->addNotice(tr("someone repeat login!"),tr("REPEAT"),true);
            a = false;
        }
    }
    return a;
}

QString LogServer::getVersion() const
{
    return version;
}

void LogServer::handleConnection()
{
    LogClient * client = dynamic_cast<LogClient *>(this->nextPendingConnection());
    client->setParent(this);
    connect(client,&LogClient::disconnected,this,&LogServer::handleDisconnect);
    connect(client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(handleError(QAbstractSocket::SocketError)));
    connect(client,&LogClient::readyRead,this,&LogServer::socketNewData);
    connect(this,&LogServer::newVersion,client,&LogClient::sendVersion);

    client->write(createConnectedData());
    //ls->addInformation(tr("New connection!ID: ") + QString::number(client->socketDescriptor()),tr("CONNECTION"),true);
}

void LogServer::handleObject(LogClient * l,QJsonObject obj)
{
    if (l != nullptr)
    {
        switch (obj.value("dataCommand").toInt()) {
        case (int)DataCommand::HeardBeat:
            handleHeardBeat(l);
            break;
        case (int)DataCommand::Login:
            handleLogin(l, obj);
            break;
        case (int)DataCommand::Logout:
            handleLogout(l, obj);
            break;
        case (int)DataCommand::SyncData:
            handleSyncData(l, obj);
            break;
        case (int)DataCommand::Version:
            handleVersion(l, obj);
            break;
        case (int)DataCommand::ClientConnected:
            handleClientConnected(l);
            break;
        }
    }
}

void LogServer::socketNewData()
{
    LogClient * client = dynamic_cast<LogClient *>(sender());
    dh->handleData(client,client->readAll());
}

void LogServer::handleError(QAbstractSocket::SocketError err)
{
    LogClient * client = dynamic_cast<LogClient *>(sender());
    //ls->addError(client->errorString(),"SOCKET",false);
}

void LogServer::handleDisconnect()
{
    LogClient * l = dynamic_cast<LogClient *>(sender());
    if (l != nullptr)
    {
        //ls->addInformation(tr("Desktop Count: ") + QString::number(lstDesktop.count()));
        //ls->addInformation(tr("Mobile Count: ") + QString::number(lstMobile.count()));
        //ls->addInformation(QString(tr("UserKey: %1 and ID: %2 disconnected from server.")).arg(l->getUserKey()).arg(l->socketDescriptor()), tr("DISCONNECTED"), true);
        if (l->getUserKey() == 0) {
            //ls->addInformation(tr("Unkown user was disconnected."));
            l->deleteLater();
        }
    }

}

void LogServer::initializeServer()
{
    bool b = this->listen(QHostAddress(addr),addr_port);
    ls->addNotice(tr("Server listen result is: ") + QString::number(b));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./data.db");
    if(db.open())
        ls->addInformation(tr("Database open successfully."));

    dh->setParent(this);
    watcher->setParent(this);
    ls->setParent(this);
    watcher->setLstDesktop(&lstDesktop);
    watcher->setLstMobile(&lstMobile);
    if (b)
        watcher->start();
}

void LogServer::incomingConnection(qintptr socketDescriptor)
{
    LogClient * client = new LogClient(this);
    client->setSocketDescriptor(socketDescriptor);
    addPendingConnection(client);
    emit newClientConnection();
}



void LogServer::setVersion(const QString &value)
{
    version = value;
    emit newVersion(createVersion());
}
QByteArray LogServer::createVersion()
{
    QVariantMap map;
    map["dataResult"] = true;
    map["dataString"] = getVersion();
    map["dataTime"] = getCurrentTimeString();
    map["dataCommand"] = (int)DataCommand::Version;
    return dh->buildData(map).toUtf8();
}

QString LogServer::getCurrentTimeString()const
{
    return QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
}

void LogServer::handleLogin(LogClient * lc,QJsonObject obj)
{
    lc->setUserLastActiveTime(QDateTime::fromString(getCurrentTimeString(),"yyyy/MM/dd hh:mm:ss"));
    QString accountKey = obj.value("dataString").toString();
    QSqlQuery query;
    QVariantMap map;
    map["dataTime"] = getCurrentTimeString();
    map["dataCommand"] = (int)DataCommand::Login;
    map["dataResult"] = false;
    map["dataString"] = 0;
    query.exec(QString("select * from UserAccount where AccountKey = '%1'").arg(accountKey));
    while(query.next())
    {
        QString aK = query.value(0).toString();
        if(aK == accountKey)
        {
            int key = dh->getRandomNumber(100000,1000000);
            switch (obj.value("dataPlatform").toInt()) {
            case (int)ClientPlatform::Desktop:
                //ls->addInformation(QString(tr("ID: %1 login platform is: %2")).arg(lc->socketDescriptor()).arg((int)ClientPlatform::Desktop),tr("LOGIN"),true);
                lstDesktop.append(lc);
                map["dataResult"] = true;
                map["dataString"] = key;
                lc->setUserKey(key);
                lc->setUserLoginKey(accountKey);
                lc->setUserPlatform(ClientPlatform::Desktop);
                //ls->addInformation(QString(tr("desktop count: %1")).arg(lstDesktop.count()));
                break;
            case (int)ClientPlatform::Mobile:
                //ls->addInformation(QString(tr("ID: %1 login platform is: %2")).arg(lc->socketDescriptor()).arg((int)ClientPlatform::Mobile),tr("LOGIN"),true);
                if(checkAccountKey(obj))
                {
                    lstMobile.append(lc);
                    map["dataResult"] = true;
                    map["dataString"] = key;
                    lc->setUserKey(key);
                    lc->setUserLoginKey(accountKey);
                    lc->setUserPlatform(ClientPlatform::Mobile);
                    //ls->addInformation(QString(tr("mobile count: %1")).arg(lstMobile.count()));
                }
                else
                    ls->addInformation(QString(tr("ID: %1 login repeat login.")).arg(lc->socketDescriptor()),tr("LOGIN"),false);
                break;
            }
        }
    }
    lc->write(dh->buildData(map).toUtf8());
}

void LogServer::handleVersion(LogClient * lc,QJsonObject obj)
{
    lc->write(createVersion());
    lc->setUserLastActiveTime(QDateTime::fromString(getCurrentTimeString(),"yyyy/MM/dd hh:mm:ss"));
}

void LogServer::handleSyncData(LogClient * lc,QJsonObject obj)
{
    lc->setUserLastActiveTime(QDateTime::fromString(getCurrentTimeString(),"yyyy/MM/dd hh:mm:ss"));
    if(lc->getUserKey() > 0)
    {
        for (int i = 0; i < lstMobile.count(); ++i)
        {
            if (lc->getUserLoginKey() == lstMobile.at(i)->getUserLoginKey())
            {
                lstMobile.at(i)->write(dh->buildData(obj.toVariantMap()).toUtf8());
                return;
            }
        }
        bool isNeedCreate = true;
        foreach (QString t, db.tables()) {
            if(t != QString("log%1").arg(lc->getUserKey()))
                isNeedCreate = true;
            else
                isNeedCreate = false;
        }
        if(isNeedCreate)
            createLogTable(lc->getUserLoginKey());
        QVariantMap map;
        map["dataCommand"] = (int)DataCommand::SyncData;
        map["dataTime"] = getCurrentTimeString();
        map["dataResult"] = addLogIntoDatabase(lc->getUserLoginKey(),obj);
        lc->write(dh->buildData(map).toUtf8());
        //ls->addInformation(tr("userKey: ") + QString::number(lc->getUserKey()) + tr(" sync data: ") + obj.value("dataString").toString());
    }
}

void LogServer::handleLogout(LogClient * lc,QJsonObject obj)
{
    for(int i = 0;i< lstDesktop.count();++i)
        if(lc == lstDesktop.at(i))
            lstDesktop.removeAt(i);
    for(int i = 0;i< lstMobile.count();++i)
        if(lc == lstMobile.at(i))
            lstMobile.removeAt(i);
    lc->setUserKey(0);
}

void LogServer::handleHeardBeat(LogClient *lc)
{
    lc->setUserLastActiveTime(QDateTime::fromString(getCurrentTimeString(),"yyyy/MM/dd hh:mm:ss"));
}

void LogServer::handleClientConnected(LogClient *lc)
{
    if(lc->getUserKey() > 0){
        //ls->addInformation(tr("client ask for connected platform!"));
        if(lc->getUserPlatform() == ClientPlatform::Desktop)
            handleDesktopClientConnected(lc);
        else if(lc->getUserPlatform() == ClientPlatform::Mobile)
            handleMobileClientConnected(lc);
    }
}

void LogServer::handleDesktopClientConnected(LogClient *lc)
{
    QVariantMap map;
    map["dataCommand"] = (int)DataCommand::ClientConnected;
    map["dataResult"] = false;
    for(int i=0;i<lstMobile.count();++i)
    {
        if(lstMobile.at(i)->getUserLoginKey() == lc->getUserLoginKey())
        {
            map["dataString"] = lstMobile.at(i)->getUserKey();
            map["dataResult"] = true;
            if(lc->isSockValid())
            {
                lc->write(dh->buildData(map).toUtf8());
                return;
            }
        }
    }
}

void LogServer::handleMobileClientConnected(LogClient *lc)
{
    QVariantMap map;
    map["dataCommand"] = (int)DataCommand::ClientConnected;
    map["dataResult"] = false;
    for(int i=0;i<lstDesktop.count();++i)
    {
        if(lstDesktop.at(i)->getUserLoginKey() == lc->getUserLoginKey())
        {
            map["dataString"] = lstDesktop.at(i)->getUserKey();
            map["dataResult"] = true;
            if(lc->isSockValid())
                lc->write(dh->buildData(map).toUtf8());
        }
    }
}

void LogServer::createLogTable(const QString & name)
{
    QSqlQuery query;
    query.exec(QString("CREATE TABLE log%1 (time  TEXT,text  TEXT,type  TEXT,note TEXT,return INTERGER)").arg(name));
}

bool LogServer::addLogIntoDatabase(const QString & name,const QJsonObject& obj)
{
    QSqlQuery query;
    return query.exec(QString("insert into log%6 (time,text,type,note,return) values ('%1','%2','%3','%4','%5')")
                      .arg(obj.value("dataTime").toString())
                      .arg(obj.value("dataString").toString())
                      .arg(getTypeName(obj.value("dataType").toInt()))
                      .arg(obj.value("dataNote").toString())
                      .arg(obj.value("dataResult").toBool())
                      .arg(name)
                      );
}
QString LogServer::getTypeName(int a)
{
    QString s = "";
    switch (a) {
    case (int)LogType::Error:
        s = tr("ERROR");
        break;
    case (int)LogType::Information:
        s = tr("INFO");
        break;
    case (int)LogType::Warning:
        s = tr("WARNING");
        break;
    case (int)LogType::Notice:
        s = tr("NOTICE");
        break;
    case (int)LogType::Verbose:
        s = tr("VERBOSE");
        break;
    }
    return s;
}
QByteArray LogServer::createConnectedData()
{
    QVariantMap map;
    map["dataCommand"] = (int)DataCommand::Connected;
    map["dataTime"] = getCurrentTimeString();
    map["dataResult"] = true;
    return dh->buildData(map).toUtf8();
}


