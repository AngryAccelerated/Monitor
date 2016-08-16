#include "logclientlifewatcher.h"

LogClientLifeWatcher::LogClientLifeWatcher(QObject *parent)
{

}

LogClientLifeWatcher::~LogClientLifeWatcher()
{
    isStop = true;
}

void LogClientLifeWatcher::run()
{
    while (!isStop) {
        QDateTime time = QDateTime::currentDateTime();
        if(!lstDesktop->isEmpty() || !lstMobile->isEmpty())
        {
            for(int i=0;i<lstDesktop->count();++i)
            {
                if(!lstDesktop->at(i)->isSockValid())
                {
                    lstDesktop->removeAt(i);
                }
                else
                {
                    if(time > lstDesktop->at(i)->getUserLastActiveTime())
                    {
                        if(lstDesktop->at(i)->getUserLastActiveTime().msecsTo(time) > timeout * 1000)
                        {
                            if(lstDesktop->at(i)->isSockValid())
                                lstDesktop->at(i)->deleteLater();
                            lstDesktop->removeAt(i);
                        }
                    }
                    QThread::msleep(10);
                }
            }

            for (int i = 0; i < lstMobile->count(); ++i)
            {
                if (!lstMobile->at(i)->isSockValid())
                {
                    lstMobile->removeAt(i);
                }
                else {
                    if (time > lstMobile->at(i)->getUserLastActiveTime())
                    {
                        if (lstMobile->at(i)->getUserLastActiveTime().msecsTo(time) > timeout * 1000)
                        {
                            if (lstMobile->at(i)->isSockValid())
                                lstMobile->at(i)->deleteLater();
                            lstMobile->removeAt(i);
                        }
                    }
                }
                QThread::msleep(10);
            }
            if((lstDesktop->count() + lstMobile->count()) < 1000)
                QThread::msleep(frequency);
            else
                QThread::msleep(frequency);
        }
    }

}




void LogClientLifeWatcher::setLstMobile(QList<LogClient *> *value)
{
    lstMobile = value;
}


void LogClientLifeWatcher::setLstDesktop(QList<LogClient *> *value)
{
    lstDesktop = value;
}

int LogClientLifeWatcher::getFrequency() const
{
    return frequency;
}

void LogClientLifeWatcher::setFrequency(int value)
{
    frequency = value;
}

