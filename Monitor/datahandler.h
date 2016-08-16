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
enum class LogType{
    Warning,
    Information,
    Notice,
    Verbose,
    Error
};
enum class Platform{
    Desktop,
    Mobile
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
    void newObject(QJsonObject obj);

public slots:

    void handleData(QByteArray data);
private:
    QByteArray buffer;
};

#endif // DATAHANDLER_H
