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

	// Don't use the terminal, which is already in use by the shell
	serverlog.setConsoleOutputFlags(Log::M_NONE);
	// Redirect output to a log file
	serverlog.setFileOutputFlags(Log::M_ALL | Log::M_AUTO_FLUSH);
	serverlog.openFile("simciv_server.log");

	serverlog.info() << "Server started" << serverlog.endl();

	m_world.generate();

	while(m_runFlag)
	{
		// Pop commands from the input queue
		std::string command = getMessage(m_input);
		if(!command.empty())
		{
			serverlog.info() << "Received command '" << command << "'" << serverlog.endl();

			if(command == "shutdown")
			{
				m_runFlag = false;
			}
			else
			{
				std::string msg = "Unknown command";
				serverlog.more() << msg << serverlog.endl();
				pushMessage(m_output, msg + '\'' + command + '\'');
			}
		}

		// Update the world
		m_server.update();

		// Sleep
		sf::sleep(sf::milliseconds(1000 / 60));
	}

	serverlog.info() << "Server closed" << serverlog.endl();
	pushMessage(m_output, "Server closed.");
}

} // namespace simciv



