#include "logset.h"

LogSet::LogSet(QObject *parent)
{
    this->setParent(parent);
}

void LogSet::outputDatabase(const QString& name)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);
    if(db.open())
    {
        QString create_table = "CREATE TABLE Logs (time  TEXT,text  TEXT,type  TEXT,note TEXT,return TEXT)";
        QSqlQuery query;
        if(query.exec(create_table))
        {
            foreach (Log l, lstLog)
                query.exec(QString("insert into Logs (time,text,type,note,return) values ('%1','%2','%3','%4','%5')")
                                      .arg(l.getDateTimeString())
                                      .arg(l.getText())
                                      .arg(l.getTypeName())
                                      .arg(l.getNote())
                                      .arg(l.getReturnValue())
                           );
        }
    }
    else
        addError(tr("Cannot Open Database"),"DATABASE",false);
    db.close();
}

void LogSet::outputTextFile(const QString &path)
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream ts(&file);
        ts << "-------------------------------------" << "\n";
        ts << "LogCollector Version: "<< version << "\n";
        ts << "Kernel Type: " << QSysInfo::kernelType() << "\n";
        ts << "Kernel Version: " << QSysInfo::kernelVersion() << "\n";
        ts << "CPU Architecture: " << QSysInfo::currentCpuArchitecture() << "\n";
        ts << "OS Name: " << QSysInfo::prettyProductName() << "\n";
        ts << "Application Path: " << appPath << "\n";
        ts << "-------------------------------------" << "\n\n";
        foreach (Log l, lstLog)
            ts << l.getLogString() << "\n";
        file.close();
    }
}
void LogSet::addWarning(const QString &t, const QString &n, bool reState){
    lstLog.append(Log(t , LogType::Warning, n, reState));
    emit newLog(Log(t , LogType::Warning, n, reState));
}

void LogSet::addError(const QString &t, const QString &n, bool reState){
    lstLog.append(Log(t , LogType::Error, n, reState));
    emit newLog(Log(t , LogType::Error, n, reState));
}

void LogSet::addInformation(const QString &t, const QString &n, bool reState){
    lstLog.append(Log(t , LogType::Information, n, reState));
    emit newLog(Log(t , LogType::Information, n, reState));
}

void LogSet::addNotice(const QString &t, const QString &n, bool reState){
    lstLog.append(Log(t , LogType::Notice, n, reState));
    emit newLog(Log(t , LogType::Notice, n, reState));
}

void LogSet::addVerbose(const QString &t, const QString &n, bool reState){
    lstLog.append(Log(t , LogType::Verbose, n, reState));
    emit newLog(Log(t , LogType::Verbose, n, reState));
}

void LogSet::setAppPath(const QString &value){
    appPath = value;
}
