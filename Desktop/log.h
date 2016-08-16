#ifndef LOG_H
#define LOG_H

#include <QDateTime>
#include <QObject>
#include <datahandler.h>
class Log
{

public:
    explicit Log(const QString& s,LogType t,const QString& n, const bool& re);
    Log(const Log& l);
    Log();
    //getters
    QString getTypeName();

    bool getReturnValue() const;

    QString getText() const;

    LogType getType() const;

    QDateTime getTime() const;

    QString getLogString();

    QString getNote() const;

    QString getDateTimeString();

    //setters
    void setType(const LogType &value);

    void setTime(const QDateTime &value);

    void setText(const QString &value);

    void setReturnValue(bool value);

    void setNote(const QString &value);

private:
    bool returnValue;

    QString text;

    QString note;

    QDateTime time;

    LogType type;
};

#endif // LOG_H
Q_DECLARE_METATYPE(Log)
