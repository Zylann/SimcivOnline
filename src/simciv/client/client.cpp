#include <iostream>
#include <cassert>
#include "client.hpp"

using namespace std;

namespace simciv
{

//------------------------------------------------------------------------------
bool Client::init()
{
	cout << "I: Client init" << endl;

	assert(m_host == nullptr);

	m_host = enet_host_create(
		nullptr, // create a client host
		1, // only allow 1 ongoing connection
		2, // allow up 2 channels to be used, 0 and 1
		57600/8, // 56K modem with 56 Kbps downstream bandwidth
		14400/8 // 56K modem with 14 Kbps upstream bandwidth
	);

	if(m_host == nullptr)
	{
		cout << "E: Client: An error occurred while trying to create an ENet client host." << endl;
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
bool Client::isConnected() const
{
	return m_peer != nullptr;
}

//------------------------------------------------------------------------------
bool Client::connect(const std::string address, u16 port)
{
	if(m_host == nullptr && !init())
	{
		return false;
	}

	if(isConnected())
	{
		// Abort previous connection if any
		cout << "I: Client: aborting previous connection before new one" << endl;
		disconnect();
	}

	cout << "I: Client: trying to connect " << address << ":" << port << "..." << endl;

	ENetAddress enetAddress;

	enet_address_set_host(&enetAddress, address.c_str());
	enetAddress.port = port;

	// Initiate the connection, allocating the two channels 0 and 1.
	m_peer = enet_host_connect(m_host, &enetAddress, 2, 0);
	if(m_peer == nullptr)
	{
		cout << "E: Client: No available peers for initiating an ENet connection." << endl;
		return false;
	}

	ENetEvent event;

	// Wait up to 5 seconds for the connection attempt to succeed.
	if(enet_host_service(m_host, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		cout << "I: Client: Connection to " << address << ":" << port << " succeeded." << endl;
		return true;
	}
	else
	{
		// Either the 5 seconds are up or a disconnect event was
		// received. Reset the peer in the event the 5 seconds
		// had run out without any significant event.
		enet_peer_reset(m_peer);
		cout << "I: Client: Connection to " << address << ":" << port << " failed." << endl;
		return false;
	}
}

//------------------------------------------------------------------------------
void Client::disconnect()
{
	if(!isConnected())
	{
		return;
	}

	ENetEvent event;

	enet_peer_disconnect(m_peer, 0);

	// Allow up to 3 seconds for the disconnect to succeed
	while(enet_host_service(m_host, &event, 3000) > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
				// Drop any received packets.
				enet_packet_destroy (event.packet);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "I: Client: disconnection succeeded." << endl;
				return;

			default:
				break;
		}
	}

	// We've arrived here, so the disconnect attempt didn't
	// succeed yet. Force the connection down.
	cout << "I: Client: disconnection timeout. Force connection down." << endl;
	enet_peer_reset(m_peer);
	m_peer = nullptr;
}

//------------------------------------------------------------------------------
bool Client::onConnect(ENetPeer * peer)
{
	cout << "I: Client: onConnect" << endl;
	return true;
}

//------------------------------------------------------------------------------
bool Client::onReceive(Blob & input, ENetPeer * peer, u8 packetType)
{
	cout << "I: Client: onReceive" << endl;
	return true;
}

//------------------------------------------------------------------------------
void Client::onDisconnect(ENetPeer * peer)
{
	cout << "I: Client: onDisconnect" << endl;
}

//------------------------------------------------------------------------------
void Client::sendToServer(const Blob & output, u32 enetFlags)
{
	assert(!output.endOfRead());

	if(isConnected())
	{
		send(output, m_peer, enetFlags);
	}
}

} // namespace simciv





