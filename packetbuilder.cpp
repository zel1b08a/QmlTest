#include <QChar>

#include "packetbuilder.h"

const quint8 PacketBuilder::_header_size    = 4;
const quint8 PacketBuilder::_check_sum_size = 2;

PacketBuilder::PacketBuilder()
    : PacketBuilderI()
{
    reset();
}

void PacketBuilder::reset()
{
    _packet = QByteArray(_header_size + _check_sum_size, char(-1));
}

void PacketBuilder::setHeaderMark(quint16 mark)
{
    *reinterpret_cast<quint16*>(_packet.data()) = mark;
}

void PacketBuilder::setType(quint8 type)
{
    _packet[3] = type;
}

void PacketBuilder::setData(const QByteArray& data)
{
    int empty_packet_size = _header_size + _check_sum_size;
    if (_packet.size() > empty_packet_size)
        _packet.remove(4, _packet.size() - empty_packet_size);
    _packet.insert(4, data);
}

QByteArray PacketBuilder::getPacket()
{
    setSize(_packet.size());
    setCheckSum(qChecksum(_packet.data(), _packet.size() - _check_sum_size));
    return _packet;
}

void PacketBuilder::setSize(quint8 size)
{
    _packet[2] = static_cast<char>(size);
}

void PacketBuilder::setCheckSum(quint16 cs)
{
    *reinterpret_cast<quint16*>(_packet.data() + _packet.size() - _check_sum_size) = cs;
}
