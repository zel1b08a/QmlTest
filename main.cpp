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

    Client client;
    ConfigModel cfg(QVector<QVector<quint32>>({
                                                  { 10, 11, 12, 13, 14 },
                                                  { 15, 16, 17, 18 },
                                                  { 19, 20 },
                                                  { 21, 22, 23, 24, 25, 26 },
                                              }));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("cfg"), &cfg);
    engine.rootContext()->setContextProperty(QStringLiteral("client"), &client);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
