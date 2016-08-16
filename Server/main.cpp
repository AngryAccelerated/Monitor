#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator trans;
    trans.load("./language/server_zh_CH.qm");
    a.installTranslator(&trans);
    qRegisterMetaType<Log>();
    MainWindow w;
    w.show();

    return a.exec();
}
