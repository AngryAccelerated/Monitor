#include <QCoreApplication>
#include <QDebug>
#include <QTranslator>
#include <logdesktop.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTranslator trans;
    trans.load("./language/desktop_zh_CH.qm");
    a.installTranslator(&trans);
    if(a.arguments().count() == 1){
        qDebug() << QObject::tr("Please Input Your Key");
        return 1;
    }
    qRegisterMetaType<Log>();
    LogSet * logSet = new LogSet();
    LogDesktop * desktop = new LogDesktop(logSet);
    desktop->setParent(&a);
    logSet->setParent(desktop);

    desktop->setUserLoginKey(a.arguments().at(1));

    return a.exec();
}

