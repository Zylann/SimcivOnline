#ifndef HEADER_SIMCIV_NETWORKHOST_HPP_INCLUDED
#define HEADER_SIMCIV_NETWORKHOST_HPP_INCLUDED

#include <enet/enet.h>
#include <fm/util/Blob.hpp>
#include "simciv/common.hpp"

namespace simciv
{

class NetworkHost
{
public:

	NetworkHost():
		m_host(nullptr)
	{}

	virtual ~NetworkHost()
	{
		if(m_host)
		{
			enet_host_destroy(m_host);
			m_host = nullptr;
		}
	}

	void update();

protected:

	// Sends a message to a peer
	void send(const Blob & output, ENetPeer * peer, u32 enetFlags = ENET_PACKET_FLAG_RELIABLE);

	// Called when the host has been connected to a peer
	virtual bool onConnect(ENetPeer * peer) = 0;

	// Called when a message is received from a peer
	virtual bool onReceive(Blob & input, ENetPeer * peer, u8 packetType) = 0;

	// Called when a peer has been disconnected
	virtual void onDisconnect(ENetPeer * peer) = 0;

	ENetHost * m_host; // local host
};

} // namespace simciv

#endif // HEADER_SIMCIV_NETWORKHOST_HPP_INCLUDED


