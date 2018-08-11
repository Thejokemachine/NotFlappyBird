#include "NetMessageManager.h"
#include <iostream>

void Network::CNetMessageManager::Init(SOCKET aSocket)
{
	mySocket = aSocket;
}

void Network::CNetMessageManager::AddReceiver(sockaddr_in aAddress)
{
	myAddresses.push_back(aAddress);
}

void Network::CNetMessageManager::Flush()
{
	for (CNetMessage*& msg : myMessages)
	{
		if (myAddresses.size() <= msg->GetData().myTargetID)
		{
			PRINT("Tried sending a message to a non-existing recipient.");
			continue;
		}

		msg->Pack();

		sockaddr_in address = myAddresses[msg->GetData().myTargetID];
		int bytes = sendto(mySocket, msg->GetBufferStart(), msg->GetBufferSize(), 0, (sockaddr*)&address, sizeof(address));
	}

	myMessages.clear();
}
