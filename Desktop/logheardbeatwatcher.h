#ifndef LOGHEARDBEATWATCHER_H
#define LOGHEARDBEATWATCHER_H

#include <QObject>
#include <QThread>

#include <datahandler.h>

class LogHeardBeatWatcher : public QThread
{
    Q_OBJECT
public:
    LogHeardBeatWatcher();
    ~LogHeardBeatWatcher();

    bool getIsStop() const;
    void setIsStop(bool value);

    DataHandler *getDataHandler() const;
    void setDataHandler(DataHandler *value);

signals:
    void sendHeardBeatPackage(QByteArray arr);
protected:
    void run();
private:
    bool isStop = false;

    QVariantMap map;

    DataHandler *dataHandler = NULL;

    unsigned long frequency = 5;
};

#endif // LOGHEARDBEATWATCHER_H
