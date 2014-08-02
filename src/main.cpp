#include <iostream>
#include "simciv/version.hpp"

#ifdef SIMCIV_SERVER
	#include "simciv/server/servershell.hpp"
#else
	#include "simciv/client/clientwindow.hpp"
#endif

using namespace std;
using namespace simciv;

int main(int argc, char*argv[])
{
    cout << "SIMCIV ";
#ifdef SIMCIV_SERVER
	cout << "SERVER";
#else
	cout << "CLIENT";
#endif
    cout << " " << version::asString() << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;

	// Initialize networking API
	if(enet_initialize() != 0)
	{
		cout << "E: Failed to initialize enet" << endl;
		return 0;
	}
	atexit(enet_deinitialize);

#ifdef SIMCIV_SERVER

	ServerShell shell;
	shell.start();

#else

	ClientWindow gameWindow;
	gameWindow.start();

#endif // SIMCIV_SERVER

	return 0;
}







