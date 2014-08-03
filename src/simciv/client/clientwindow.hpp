#ifndef HEADER_SIMCIV_CLIENTWINDOW_H_INCLUDED
#define HEADER_SIMCIV_CLIENTWINDOW_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "simciv/core/world.hpp"
#include "client.hpp"

namespace simciv
{

class ClientWindow
{
public:

	void start();

private:

	sf::RenderWindow m_window;

	Client m_client;
	World m_world;
};

} // namespace simciv


#endif // HEADER_SIMCIV_CLIENTWINDOW_H_INCLUDED
