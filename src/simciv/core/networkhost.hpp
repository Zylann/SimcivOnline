#ifndef HEADER_SIMCIV_NETWORKHOST_HPP_INCLUDED
#define HEADER_SIMCIV_NETWORKHOST_HPP_INCLUDED

#include <enet/enet.h>
#include <fm/util/Blob.hpp>
#include <fm/util/Log.hpp>
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

	// Sets the log system to be used (if the global one can't be used)
	inline void setLog(zn::Log & log) { r_log = &log; }

protected:

	// Sends a message to a peer
	void send(const Blob & output, ENetPeer * peer, u32 enetFlags);

	// Called when the host has been connected to a peer
	virtual bool onConnect(ENetPeer * peer) = 0;

	// Called when a message is received from a peer
	virtual bool onReceive(Blob & input, ENetPeer * peer, u8 packetType) = 0;

	// Called when a peer has been disconnected
	virtual void onDisconnect(ENetPeer * peer) = 0;

	ENetHost * m_host; // local host
	zn::Log * r_log;
};

} // namespace simciv

#endif // HEADER_SIMCIV_NETWORKHOST_HPP_INCLUDED


