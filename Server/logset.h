#ifndef LOGSET_H
#define LOGSET_H

#include <QObject>
#include <QDateTime>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSysInfo>

#include <log.h>

class LogSet : public QObject
{
    Q_OBJECT
public:
    LogSet(QObject * parent = 0);

    void addWarning(const QString& t,const QString& n = tr("NONE"),bool reState = true);

    void addError(const QString& t,const QString& n = tr("NONE"),bool reState = true);

    void addInformation(const QString& t,const QString& n = tr("NONE"),bool reState = true);

    void addNotice(const QString& t,const QString& n = tr("NONE"),bool reState = true);

    void addVerbose(const QString& t,const QString& n = tr("NONE"),bool reState = true);

    void setAppPath(const QString &value);

    void outputTextFile(const QString &path);

    void outputDatabase(const QString &name);

    QList<Log> lstLog;
signals:

    void newLog(Log l);

private:
    QString appPath;

    QString version = "0.1";
};

#endif // LOGSET_H
