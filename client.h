#pragma once

#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>

class Client : public QTcpSocket
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);

    Q_INVOKABLE void makeConnection();
    Q_INVOKABLE void makeRequest();

public slots:
    void onHostFound();
    void onConnectedState();
    void onErrorOccured(QAbstractSocket::SocketError error);
    void onStateChanged(QAbstractSocket::SocketState state);
    void onReadyRead();

private:
    static const QHostAddress _host_address;
    static const quint16 _host_port;
};
