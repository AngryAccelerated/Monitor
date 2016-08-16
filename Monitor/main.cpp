#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtQml>
#include <logmobile.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));
    QQuickStyle::setStyle("Material");
    qmlRegisterType<LogMobile>("Mobile",1,0,"Mobile");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
