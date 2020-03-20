#include <QDebug>

#include "packetmanager.h"
#include "packetinfo.h"

using namespace PacketInfo;

PacketManager::PacketManager(QObject* parent)
    : QObject(parent)
    , _builder(QSharedPointer<PacketBuilderI>(new PacketBuilder()))
{
}

QByteArray PacketManager::makePacket(quint8 type, const QByteArray& data)
{
    _builder->reset();
    _builder->setHeaderMark(header_mark);
    _builder->setType(type);
    _builder->setData(data);
    return _builder->getPacket();
}

void PacketManager::parsePacket(const QByteArray& data)
{
    quint8 empty_packet_size = header_size + check_sum_size;
    auto data_size = data.size();
    auto bound = data_size - empty_packet_size;
    quint8 packet_size;
    for (auto id = 0; id < bound;) {
        if (data.at(id) == static_cast<char>(header_mark & 0xFF)
            && data.at(id + 1) == static_cast<char>((header_mark & 0xFF00) >> 8)) {
            packet_size = data.at(id + 2);
            if (id + packet_size < bound) {

            } else id = bound;
        } else ++id;
    }
}
