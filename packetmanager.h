#pragma once

#include <QSharedPointer>

#include "packetbuilder.h"

class PacketManager : QObject
{
    Q_OBJECT

public:
    PacketManager(QObject* parent = nullptr);

    QByteArray makePacket(quint8 type, const QByteArray& data);
    void parsePacket(const QByteArray& data);

signals:
    void packetReady(QByteArray packet);

private:
    QSharedPointer<PacketBuilderI> _builder;
};
