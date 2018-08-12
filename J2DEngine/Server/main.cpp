#include "../Engine/Network/Server.h"
#include "Utilities/Time.h"

int main()
{
	CTime::GetInstance().Init();

	Network::CServer server;
	server.Start();

	while (true)
	{
		CTime::GetInstance().Update();
		server.Update();
	}
}