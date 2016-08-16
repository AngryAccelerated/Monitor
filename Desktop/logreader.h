#ifndef LOGREADER_H
#define LOGREADER_H

#include <QObject>
#include <QThread>
#include <QSettings>

class LogReader : public QThread
{
    Q_OBJECT
public:
    LogReader();
signals:
    void newInformation(int type,QString text,QString note,bool result);
protected:
    void run();
private:
    bool isStop = false;
};

#endif // LOGREADER_H
