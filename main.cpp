#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client.h"
#include "bank.h"
#include "bankmodel.h"
#include "configmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qRegisterMetaType<QAbstractSocket::SocketError>();
    qRegisterMetaType<QAbstractSocket::SocketState>();
    qRegisterMetaType<Bank*>();
    qmlRegisterType<BankModel>("Config", 1, 0, "BankModel");
    qmlRegisterType<ConfigModel>("Config", 1, 0, "ConfigModel");
    qmlRegisterUncreatableType<Bank>("Config", 1, 0, "Bank", QStringLiteral("Don't!"));

    Client client;
    ConfigModel cfg;
    cfg.setBanks(QList<Bank*>()
                 << new Bank(QVector<Coefficient>({ Coefficient { 11 }, Coefficient { 21 }, Coefficient { 31 }, Coefficient { 41 } }))
                 << new Bank(QVector<Coefficient>({ Coefficient { 12 }, Coefficient { 22 }, Coefficient { 32 }, Coefficient { 42 } }))
                 << new Bank(QVector<Coefficient>({ Coefficient { 13 }, Coefficient { 23 }, Coefficient { 33 }, Coefficient { 43 } }))
                 << new Bank(QVector<Coefficient>({ Coefficient { 14 }, Coefficient { 24 }, Coefficient { 34 }, Coefficient { 44 } }))
                 << new Bank(QVector<Coefficient>({ Coefficient { 15 }, Coefficient { 25 }, Coefficient { 35 }, Coefficient { 45 } }))
                 );

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("cfg"), &cfg);
    engine.rootContext()->setContextProperty(QStringLiteral("client"), &client);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
