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
//			cout << "I: NetworkHost: A packet of length " << event.packet->dataLength
//				<< " containing " << event.packet->data
//				<< " was received from " << event.peer->data
//				<< " on channel " << event.channelID << endl;

			Blob packet;
			packet.append(event.packet->data, event.packet->dataLength);

			// Clean up the packet now we're done using it
			enet_packet_destroy(event.packet);

			if(!packet.endOfRead())
			{
				u8 packetType;
				packet >> packetType;
				onReceive(packet, event.peer, packetType);
//				{
//					cout << "I: NetworkHost: unknown packet type (" << (u32)packetType << ")" << endl;
//				}
			}
//			else
//			{
//				cout << "I: NetworkHost: received empty packet" << endl;
//			}
		}
		break;

		case ENET_EVENT_TYPE_DISCONNECT:
//			cout << "I: NetworkHost: " << event.peer->data << " disconnected" << endl;
			onDisconnect(event.peer);
			// Reset the peer's client information
			event.peer->data = nullptr;
			break;

		default:
//			cout << "I: NetworkHost: wack?" << endl;
			break;
		}
	}

	if(hostRetval < 0)
	{
		cout << "E: NetworkHost: service_host failed" << endl;
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





