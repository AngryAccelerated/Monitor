#ifndef LOGCLIENTLIFEWATCHER_H
#define LOGCLIENTLIFEWATCHER_H

#include <QObject>
#include <QThread>
#include <logclient.h>

class LogClientLifeWatcher : public QThread
{
public:
    LogClientLifeWatcher(QObject * parent = 0);
    ~LogClientLifeWatcher();

    int getFrequency() const;
    void setFrequency(int value);


    void setLstDesktop(QList<LogClient *> *value);

    void setLstMobile(QList<LogClient *> *value);


protected:
    void run();
private:
    bool isStop = false;

    int frequency = 1000;

    int timeout = 20;

    QList<LogClient*> * lstDesktop;

    QList<LogClient*> * lstMobile;


};

#endif // LOGCLIENTLIFEWATCHER_H
