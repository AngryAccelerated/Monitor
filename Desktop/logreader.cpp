#include "logreader.h"

LogReader::LogReader()
{

}

void LogReader::run()
{
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\LogDesktop",QSettings::NativeFormat);
    while(!isStop){
        if(settings.value("IsRead").toInt() == 0)
        {
            settings.setValue("IsRead",1);
            emit newInformation(
                        settings.value("Level").toInt(),
                        settings.value("Text").toString(),
                        settings.value("Note").toString(),
                        settings.value("Result").toBool()
                                );
        }
        QThread::msleep(1200);
    }
}
