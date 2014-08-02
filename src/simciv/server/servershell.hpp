#ifndef HEADER_SIMCIV_SERVERSHELL_HPP_INCLUDED
#define HEADER_SIMCIV_SERVERSHELL_HPP_INCLUDED

#include <SFML/System.hpp>
#include <queue>
#include "server.hpp"
#include "simciv/world.hpp"

namespace simciv
{

class ServerShell
{
public:

	ServerShell():
		m_thread(&ServerShell::asyncMainLoop, this),
		m_runFlag(false)
	{}

	~ServerShell()
	{
	}

	void start();

private:

	std::string getMessage(std::queue<std::string> & messageQueue);
	std::string waitMessage(std::queue<std::string> & messageQueue);
	void pushMessage(std::queue<std::string> & messageQueue, const std::string msg);

	void asyncMainLoop();

	sf::Thread m_thread;

	// Shared variables

	std::queue<std::string> m_input;
	std::queue<std::string> m_output;

	// Mutex used to access shared variables

	sf::Mutex m_ioMutex;

	// Thread-accessed members

	World m_world;
	Server m_server;
	bool m_runFlag;
};

} // namespace simciv

#endif // HEADER_SIMCIV_SERVERSHELL_HPP_INCLUDED
