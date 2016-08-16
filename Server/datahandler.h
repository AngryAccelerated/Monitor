/*
time: 2016/07/15
writer: Accelerated

This class could parse the json data and create json data for sync.
*/
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QTime>
#include <QDebug>
#include <logclient.h>

enum class DataCommand{
    Login,
    Logout,
    Version,
    HeardBeat,
    SyncData,
    Connected,
    ClientConnected,
    Shutdown
};
enum class LogType {
    Warning,
    Information,
    Notice,
    Verbose,
    Error
};
class DataHandler : public QObject
{
    Q_OBJECT
public:
    explicit DataHandler(QObject *parent = 0);

    QString buildData(const QVariantMap & map);

    QJsonObject convertDataToJson(const QString & data);

    int getRandomNumber(int min, int max);
signals:
    void newObject(LogClient * l,QJsonObject obj);

    void newObjectWithoutClient(QJsonObject obj);

public slots:
    void handleData(LogClient *l, QByteArray data);
private:
    QByteArray buffer;
};

#endif // DATAHANDLER_H
