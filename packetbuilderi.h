#pragma once

#include <QtGlobal>
#include <QByteArray>

class PacketBuilderI
{
public:
    virtual ~PacketBuilderI() = default;

    virtual void reset() = 0;
    virtual void setHeaderMark(quint16 mark) = 0;
    virtual void setType(quint8 type) = 0;
    virtual void setData(const QByteArray& data) = 0;
    virtual QByteArray getPacket() = 0;

protected:
    virtual void setSize(quint8 size) = 0;
    virtual void setCheckSum(quint16 cs) = 0;
};
