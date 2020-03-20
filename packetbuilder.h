#pragma once

#include "packetbuilderi.h"

class PacketBuilder : public PacketBuilderI
{
public:
    PacketBuilder();
    ~PacketBuilder() = default;

    // PacketBuilderI interface
public:
    void reset() override;
    void setHeaderMark(quint16 mark) override;
    void setType(quint8 type) override;
    void setData(const QByteArray& data) override;
    QByteArray getPacket() override;

    // PacketBuilderI interface
protected:
    void setSize(quint8 size) override;
    void setCheckSum(quint16 cs) override;

private:
    static const quint8 _header_size;       //  bytes
    static const quint8 _check_sum_size;    //  bytes

    QByteArray _packet;
};
