#include <QTimer>

#include "client.h"


const QHostAddress Client::_host_address = QHostAddress("10.11.5.170");
const quint16 Client::_host_port = 13032;


Client::Client(QObject *parent)
    : QTcpSocket(parent)
{
    connect(this, &Client::hostFound   , this, &Client::onHostFound     , Qt::DirectConnection);
    connect(this, &Client::connected   , this, &Client::onConnectedState, Qt::DirectConnection);
    connect(this, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &Client::onErrorOccured, Qt::DirectConnection);
    connect(this, &Client::stateChanged, this, &Client::onStateChanged  , Qt::DirectConnection);
    connect(this, &Client::readyRead   , this, &Client::onReadyRead     , Qt::DirectConnection);

    makeConnection();
}

void Client::makeConnection()
{
    connectToHost(_host_address, _host_port);
}

void Client::makeRequest()
{
    QByteArray data;
    qint64 bytes = write(data);
    if (bytes != data.size())
        qWarning() << tr("bad transaction!");
}

void Client::onHostFound()
{
    qInfo() << tr("host was found");
}

void Client::onConnectedState()
{
    qInfo() << tr("connection established");
}

void Client::onErrorOccured(QAbstractSocket::SocketError error)
{
    switch (error) {
    case ConnectionRefusedError          : break;
    case RemoteHostClosedError           : break;
    case HostNotFoundError               : break;
    case SocketAccessError               : break;
    case SocketResourceError             : break;
    case SocketTimeoutError              : break;
    case DatagramTooLargeError           : break;
    case NetworkError                    : break;
    case AddressInUseError               : break;
    case SocketAddressNotAvailableError  : break;
    case UnsupportedSocketOperationError : break;
    case UnfinishedSocketOperationError  : break;
    case ProxyAuthenticationRequiredError: break;
    case SslHandshakeFailedError         : break;
    case ProxyConnectionRefusedError     : break;
    case ProxyConnectionClosedError      : break;
    case ProxyConnectionTimeoutError     : break;
    case ProxyNotFoundError              : break;
    case ProxyProtocolError              : break;
    case OperationError                  : break;
    case SslInternalError                : break;
    case SslInvalidUserDataError         : break;
    case TemporaryError                  : break;
    case UnknownSocketError              : break;
    }
    qDebug() << tr("error: %1").arg(error);
}

void Client::onStateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case UnconnectedState:
    {
        qInfo() << tr("connection closed"); break;
        QTimer::singleShot(5000, this, &Client::makeConnection);
        break;
    }

    case HostLookupState : qInfo() << tr("looking for host"); break;
    case ConnectingState : qInfo() << tr("trying to connect"); break;
    case ConnectedState  : break;
    case BoundState      : qInfo() << tr("bound state"); break;
    case ListeningState  : qInfo() << tr("listening port"); break;
    case ClosingState    : qInfo() << tr("closing connection"); break;
    }
}

void Client::onReadyRead()
{
    QByteArray data = readLine();
    //  handle packet
}
