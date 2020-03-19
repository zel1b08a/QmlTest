#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client.h"
#include "configmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qRegisterMetaType<QAbstractSocket::SocketError>();
    qRegisterMetaType<QAbstractSocket::SocketState>();
//    qmlRegisterType<ConfigModel>("Config", 1, 0, "ConfigModel");

    Client client;
    ConfigModel cfg(QVector<QVector<quint32>>({
                                                  { 10, 12, 23, 34, 45 },
                                                  { 10, 12, 23, 34 },
                                                  { 10, 12 },
                                                  { 10, 12, 23, 34, 45, 46 },
                                              }));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("cfg"), &cfg);
    engine.rootContext()->setContextProperty(QStringLiteral("client"), &client);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
