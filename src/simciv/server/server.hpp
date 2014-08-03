#ifndef HEADER_SIMCIV_SERVER_HPP_INCLUDED
#define HEADER_SIMCIV_SERVER_HPP_INCLUDED

#include <fm/util/Log.hpp>
#include "simciv/core/networkhost.hpp"

namespace simciv
{

class Server : public NetworkHost
{
public:

	Server():
		NetworkHost()
	{}

	~Server()
	{}

	bool init();

protected:

	bool onConnect(ENetPeer * peer) override;
	bool onReceive(Blob & input, ENetPeer * peer, u8 packetType) override;
	void onDisconnect(ENetPeer * peer) override;

	ENetAddress m_address;
};

extern Log serverlog;

} // namespace simciv

#endif // HEADER_SIMCIV_SERVER_HPP_INCLUDED

