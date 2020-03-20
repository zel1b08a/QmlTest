#pragma once

#include <QtGlobal>
#include <QByteArray>

namespace PacketInfo {

    constexpr quint16 header_mark = 0x08497;
    constexpr quint8 header_size = 4;
    constexpr quint8 check_sum_size = 2;

    enum Type : quint8 {
        ConfigType,
        UnknownType
    };

    bool isValid(const QByteArray& packet)
    {
        if (packet.isEmpty())
            return false;

        if (packet.at(2) != packet.size())
            return false;

        if (packet.at(3) == UnknownType)
            return false;

        quint16 packet_cs = *reinterpret_cast<quint16*>(packet.mid(packet.size() - check_sum_size).data());
        if (packet_cs != qChecksum(packet.data(), packet.size() - check_sum_size))
            return false;

        return true;
    }

    inline quint16 packetMark(const QByteArray& packet)
    {
        return packet.size() >= 2 ? *reinterpret_cast<const quint16*>(packet.data()) : 0;
    }

    inline quint8 packetSize(const QByteArray& packet)
    {
        return packet.size() >= 3 ? static_cast<quint8>(packet.at(2)) : 0;
    }

    inline Type packetType(const QByteArray& packet)
    {
        return packet.size() >= 4 ? static_cast<Type>(packet.at(3)) : UnknownType;
    }

    inline QByteArray packetData(const QByteArray& packet)
    {
        return isValid(packet) ? packet.mid(4, packetSize(packet)) : QByteArray();
    }

    inline quint16 packetCheckSum(const QByteArray& packet)
    {
        return packet.size() >= 2 ? *reinterpret_cast<const quint16*>(packet.data() + packet.size() - sizeof(quint16)) : 0;
    }

}
