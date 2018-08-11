#include "Server.h"
#include <string>

void Network::CServer::Start()
{
	PRINT("Starting up server...");
	CConnectionBase::Start();

	unsigned short port = 54000;
	myLocalAddress.sin_family = AF_INET;
	myLocalAddress.sin_port = htons(port);
	myLocalAddress.sin_addr.s_addr = INADDR_ANY;

	int error = bind(mySocket, (sockaddr*)&myLocalAddress, sizeof(myLocalAddress));
	if (error != 0)
	{
		PRINT("Binding of local address failed with error code: " + std::to_string(error));
		return;
	}

	PRINT("Listening for new connections on port: " + std::to_string(port));
}

void Network::CServer::Update()
{
	CConnectionBase::Update();

	for (SReceivedMessage& rec : myReceivedBuffer)
	{
		char* buffer = rec.myBuffer;
		ENetMessageType type = static_cast<ENetMessageType>(buffer[0]);

		switch (type)
		{
		case Network::ENetMessageType::Chat:
		{
			CNetMessageChat msg;
			msg.ReceiveData(buffer, sizeof(SNetMessageChatData));
			msg.Unpack();
			PRINT("Received: " + msg.GetData().myMessage.ToString());
			break;
		}
		case Network::ENetMessageType::Ping:
		{
			CNetMessagePing msg;
			msg.ReceiveData(buffer, sizeof(SNetMessagePingData));
			msg.Unpack();
			PRINT("Received ping from ");
			break;
		}
		case Network::ENetMessageType::Connect:
		{
			CNetMessageConnect msg;
			msg.ReceiveData(buffer, sizeof(SNetMessageConnectData));
			msg.Unpack();
			AddClient(rec.myFromAddress, msg.GetData().myName.ToString());
			break;
		}
		}
	}
}

void Network::CServer::Stop()
{
	CConnectionBase::Stop();
}

void Network::CServer::AddClient(sockaddr_in aAddress, const std::string & aName)
{
	unsigned long ID = aAddress.sin_addr.S_un.S_addr;

	if (myClients.find(ID) == myClients.end())
	{
		SClient newClient;
		newClient.myName = aName;
		newClient.myID = myClients.size();

		myClients.insert(std::make_pair(ID, newClient));
		PRINT(aName + " connected!");

		SNetMessageConnectData response;
		response.myName = "Server";
		response.myTargetID = newClient.myID;
		
		myMessageManager.CreateMessage<CNetMessageConnect>(response);
		myMessageManager.AddReceiver(aAddress);

		for (auto& client : myClients)
		{
			if (client.first == ID)
				continue;

			SNetMessageData newPlayerMessage;
			newPlayerMessage.myTargetID = client.second.myID;
			newPlayerMessage.myType = ENetMessageType::NewPlayer;
			newPlayerMessage.myID = newClient.myID;

			myMessageManager.CreateMessage<CNetMessage>(newPlayerMessage);
		}
	}
	else
	{
		PRINT("Tried to add an already existing client.");
	}
}