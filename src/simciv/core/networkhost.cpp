#include <iostream>
#include "networkhost.hpp"

using namespace std;

namespace simciv
{

//------------------------------------------------------------------------------
void NetworkHost::update()
{
	ENetEvent event;

	s32 hostRetval = 0;
	while((hostRetval = enet_host_service(m_host, &event, 0)) > 0)
	{
		switch(event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			onConnect(event.peer);
			break;

		case ENET_EVENT_TYPE_RECEIVE:
		{
			Blob packet;
			packet.append(event.packet->data, event.packet->dataLength);

			// Clean up the packet now we're done using it
			enet_packet_destroy(event.packet);

			if(!packet.endOfRead())
			{
				u8 packetType;
				packet >> packetType;
				onReceive(packet, event.peer, packetType);
			}
			else
			{
				if(r_log)
				{
					r_log->warn() << "NetworkHost: Received empty packet" << r_log->endl();
				}
			}
		}
		break;

		case ENET_EVENT_TYPE_DISCONNECT:
			onDisconnect(event.peer);
			// Reset the peer's client information
			event.peer->data = nullptr;
			break;

		default:
			// Drop unknown packet
			break;
		}
	}

	if(hostRetval < 0)
	{
		if(r_log)
		{
			r_log->err() << "NetworkHost: service_host failed" << r_log->endl();
		}
	}
}

//------------------------------------------------------------------------------
void NetworkHost::send(const Blob & output, ENetPeer * peer, u32 enetFlags)
{
	// TODO perform data compression on big packets (zlib?)

	ENetPacket * packet = enet_packet_create(
		output.getData(),
		output.getDataSize(),
		enetFlags
	);

	// Send the packet to the peer over channel id 0.
	// One could also broadcast the packet by
	// enet_host_broadcast (host, 0, packet);
	enet_peer_send(peer, 0, packet);
}

} // namespace simciv





