#include "../Engine/Network/Server.h"

int main()
{
	Network::CServer server;
	server.Start();

	while (true)
	{
		server.Update();
	}
}