#include "logheardbeatwatcher.h"

LogHeardBeatWatcher::LogHeardBeatWatcher()
{
    map["dataCommand"] = (int)DataCommand::HeardBeat;
}

LogHeardBeatWatcher::~LogHeardBeatWatcher()
{
    isStop = true;
}

void LogHeardBeatWatcher::run()
{
    while (!isStop) {
        if(dataHandler != NULL)
            emit sendHeardBeatPackage(dataHandler->buildData(map).toUtf8());
        QThread::msleep(frequency * 1000);
    }
}

DataHandler *LogHeardBeatWatcher::getDataHandler() const
{
    return dataHandler;
}

void LogHeardBeatWatcher::setDataHandler(DataHandler *value)
{
    dataHandler = value;
}

bool LogHeardBeatWatcher::getIsStop() const
{
    return isStop;
}

void LogHeardBeatWatcher::setIsStop(bool value)
{
    isStop = value;
}

