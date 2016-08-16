#include "log.h"

Log::Log(const QString &s, LogType t, const QString &n, const bool &re) :
    text(s),
    type(t),
    note(n),
    returnValue(re),
    time(QDateTime::currentDateTime())
{
}

Log::Log(const Log &l)
{
    this->text = l.text;
    this->type = l.type;
    this->note = l.note;
    this->time = l.time;
    this->returnValue = l.returnValue;
}

Log::Log()
{

}

QString Log::getTypeName(){
    QString s = "";
    switch (type) {
    case LogType::Error:
        s = QObject::trUtf8("Error");
        break;
    case LogType::Information:
        s = QObject::trUtf8("Information");
        break;
    case LogType::Warning:
        s = QObject::trUtf8("Warning");
        break;
    case LogType::Notice:
        s = QObject::trUtf8("Notice");
        break;
    case LogType::Verbose:
        s = QObject::trUtf8("Verbose");
        break;
    }
    return s;
}

LogType Log::getType() const
{
    return type;
}

void Log::setType(const LogType &value)
{
    type = value;
}

QDateTime Log::getTime() const
{
    return time;
}

QString Log::getLogString(){
    return QString(QObject::trUtf8("%1 [%2] `%4` <%5> : %3")).arg(time.toString("yyyy/MM/dd hh:mm:ss"))
            .arg(getTypeName())
            .arg(getText())
            .arg(getNote())
            .arg(getReturnValue());
}

void Log::setTime(const QDateTime &value)
{
    time = value;
}

QString Log::getText() const
{
    return text;
}

void Log::setText(const QString &value)
{
    text = value;
}
bool Log::getReturnValue() const
{
    return returnValue;
}

void Log::setReturnValue(bool value)
{
    returnValue = value;
}

QString Log::getNote() const
{
    return note;
}

QString Log::getDateTimeString(){
    return time.toString("yyyy/MM/d hh:mm:ss");
}

void Log::setNote(const QString &value)
{
    note = value;
}

