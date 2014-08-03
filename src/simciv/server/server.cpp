#include <iostream>
#include "server.hpp"

using namespace std;

namespace simciv
{

//------------------------------------------------------------------------------
bool Server::init()
{
	// Bind the server to the default localhost.
	// A specific host address can be specified by
	// enet_address_set_host (& address, "x.x.x.x");
	m_address.host = ENET_HOST_ANY;
	m_address.port = SIMCIV_DEFAULT_PORT;

	m_host = enet_host_create(
		&m_address, // the address to bind the server host to
		32, // allow up to 32 clients and/or outgoing connections
		2, // allow up to 2 channels to be used, 0 and 1
		0, // assume any amount of incoming bandwidth
		0 // assume any amount of outgoing bandwidth
	);

	if(m_host == nullptr)
	{
		cout << "E: Server: An error occurred while trying to create an ENet server host." << endl;
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
bool Server::onConnect(ENetPeer* peer)
{
	cout << "I: Server: onConnect" << endl;
	return true;
}

//------------------------------------------------------------------------------
bool Server::onReceive(Blob& input, ENetPeer* peer, u8 packetType)
{
	cout << "I: Server: onReceive" << endl;
	return true;
}

//------------------------------------------------------------------------------
void Server::onDisconnect(ENetPeer* peer)
{
	cout << "I: Server: onDisconnect" << endl;
}


} // namespace simciv



