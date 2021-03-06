#include "clientwindow.hpp"
#include "simciv/version.hpp"

namespace simciv
{

//------------------------------------------------------------------------------
void ClientWindow::start()
{
	m_client.connect("127.0.0.1", SIMCIV_DEFAULT_PORT);

	sf::ContextSettings contextSettings(
		0, // Depth buffer bits
		0, // Stencil buffer bits
		false // Anti-alias
	);

	m_window.create(
		sf::VideoMode(800,600),
		"Simciv client - " + version::asString(),
		sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,
		contextSettings
	);

	while(m_window.isOpen())
	{
		sf::Event event;
		while(m_window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				m_window.close();
			}
			else if(event.type == sf::Event::MouseButtonPressed)
			{
				Blob testPacket;
				testPacket << 42;
				testPacket << "This is a test";
				std::cout << "Sending stuff" << std::endl;
				m_client.sendToServer(testPacket);
			}
		}

		m_window.clear(sf::Color(16,16,16));
		m_window.display();
	}
}

} // namespace simciv

