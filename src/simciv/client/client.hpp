#ifndef HEADER_SIMCIV_CLIENT_HPP_INCLUDED
#define HEADER_SIMCIV_CLIENT_HPP_INCLUDED

#include "simciv/core/networkhost.hpp"

namespace simciv
{

class Client : public NetworkHost
{
public:

	Client():
		NetworkHost(),
		m_peer(nullptr)
	{}

	~Client()
	{
		disconnect();
	}

	bool connect(const std::string address, u16 port);
	void disconnect();
	bool isConnected() const;

	void sendToServer(const Blob & output, u32 enetFlags = ENET_PACKET_FLAG_RELIABLE);

protected:

	bool onConnect(ENetPeer * peer) override;
	bool onReceive(Blob & input, ENetPeer * peer, u8 packetType) override;
	void onDisconnect(ENetPeer * peer) override;

private:

	bool init();

	ENetPeer * m_peer; // remote server

};

} // namespace simciv

#endif // HEADER_SIMCIV_CLIENT_HPP_INCLUDED

