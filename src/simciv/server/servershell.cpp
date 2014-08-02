#include "servershell.hpp"

namespace simciv
{

//------------------------------------------------------------------------------
void ServerShell::start()
{
	m_runFlag = true;
	m_thread.launch();

	while(m_runFlag)
	{
		std::string command;

		std::cout << "server> ";
		std::cin >> command;

		pushMessage(m_input, command);

		std::string answer = waitMessage(m_output);
		std::cout << answer << std::endl;
	}
}

//------------------------------------------------------------------------------
std::string ServerShell::waitMessage(std::queue<std::string> & messageQueue)
{
	std::string m;
	while(m.empty())
	{
		m = getMessage(messageQueue);
		sf::sleep(sf::milliseconds(100));
	}
	return m;
}

//------------------------------------------------------------------------------
std::string ServerShell::getMessage(std::queue<std::string> & messageQueue)
{
	std::string m;
	sf::Lock lock(m_ioMutex);
	if(!messageQueue.empty())
	{
		m = messageQueue.front();
		messageQueue.pop();
	}
	return m;
}

//------------------------------------------------------------------------------
void ServerShell::pushMessage(std::queue<std::string> & messageQueue, const std::string msg)
{
	sf::Lock lock(m_ioMutex);
	messageQueue.push(msg);
}

//------------------------------------------------------------------------------
void ServerShell::asyncMainLoop()
{
	m_runFlag = m_server.init();

	while(m_runFlag)
	{
		// Pop commands from the input queue
		std::string command = getMessage(m_input);
		if(!command.empty())
		{
			if(command == "shutdown")
			{
				m_runFlag = false;
			}
			else
			{
				pushMessage(m_output, "Unknown command '" + command + "'");
			}
		}

		// Update the world
		m_server.update();

		// Sleep
		sf::sleep(sf::milliseconds(1000 / 60));
	}

	pushMessage(m_output, "Server closed.");
}

} // namespace simciv

