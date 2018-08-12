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

unsigned int Network::CNetMessageManager::Flush()
{
	unsigned int bytesSent = 0;

	for (CNetMessage*& msg : myMessages)
	{
		if (myAddresses.size() <= msg->GetBaseData().myTargetID)
		{
			PRINT("Tried sending a message to a non-existing recipient.");
			continue;
		}

		msg->Pack();

		sockaddr_in address = myAddresses[msg->GetBaseData().myTargetID];
		bytesSent += sendto(mySocket, msg->GetBufferStart(), msg->GetBufferSize(), 0, (sockaddr*)&address, sizeof(address));
	}

	myMessages.clear();

	return bytesSent;
}
