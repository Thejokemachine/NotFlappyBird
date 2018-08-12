#include "Server.h"
#include <string>
#include "Utilities/Time.h"

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

	mySendPlayerDataTimer.Init(CTimedEvent::EType::Repeat, FREQ_PLAYERDATA, [this]() { SendPlayerData(); });
	mySendPlayerDataTimer.Start();
}

void Network::CServer::Update()
{
	CConnectionBase::Update();

	float dt = CTime::GetInstance().GetDeltaTime();

	mySendPlayerDataTimer.Update(dt);

	HandleClients();

	for (SReceivedMessage& rec : myReceivedBuffer)
	{
		unsigned long senderID = ConvertAddressToID(rec.myFromAddress);
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
			ReceivePing(senderID);
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
		case ENetMessageType::PlayerData:
		{
			CNetMessagePlayerData msg;
			msg.ReceiveData(buffer, sizeof(SNetMessagePlayerDataData));
			msg.Unpack();
			CSprite& sprite = myClients[senderID].mySprite;
			sprite.SetPosition(msg.GetData().myPosition);
			sprite.SetRotation(msg.GetData().myRotation);
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
		newClient.myTimeSinceLatestPing = 0;
		newClient.myConnected = true;

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

			// New to existing
			SNetMessageData newPlayerMessage;
			newPlayerMessage.myTargetID = client.second.myID;
			newPlayerMessage.myType = ENetMessageType::NewPlayer;
			newPlayerMessage.myID = newClient.myID;

			myMessageManager.CreateMessage<CNetMessage>(newPlayerMessage);

			// Existing to new
			newPlayerMessage.myTargetID = newClient.myID;
			newPlayerMessage.myType = ENetMessageType::NewPlayer;
			newPlayerMessage.myID = client.second.myID;

			myMessageManager.CreateMessage<CNetMessage>(newPlayerMessage);
		}
	}
	else
	{
		PRINT("Tried to add an already existing client.");
	}
}

void Network::CServer::SendPlayerData()
{
	for (auto& client1 : myClients)
	{
		if (client1.second.myConnected == false)
			continue;

		for (auto& client2 : myClients)
		{
			if (client1.second.myID == client2.second.myID || client2.second.myConnected == false)
				continue;

			SNetMessagePlayerDataData data;
			data.myTargetID = client1.second.myID;
			data.myPosition = client2.second.mySprite.GetPosition();
			data.myRotation = client2.second.mySprite.GetRotation();
			data.myID = client2.second.myID;

			myMessageManager.CreateMessage<CNetMessagePlayerData>(data);
		}
	}
	PRINT("Sent player data");
}

void Network::CServer::ReceivePing(unsigned long aID)
{
	myClients[aID].myTimeSinceLatestPing = 0.f;
	PRINT("Received ping from " + std::to_string(myClients[aID].myID));
}

void Network::CServer::HandleClients()
{
	float dt = CTime::GetInstance().GetDeltaTime();

	for (auto& clientPair : myClients)
	{
		if (clientPair.second.myConnected == false)
			continue;

		clientPair.second.myTimeSinceLatestPing += dt;

		if (clientPair.second.myTimeSinceLatestPing > PING_TIMEOUT)
		{
			DisconnectClient(clientPair.second);
		}
	}
}

void Network::CServer::DisconnectClient(SClient & aClientToDisconnect)
{
	aClientToDisconnect.myConnected = false;

	PRINT("Client " + std::to_string(aClientToDisconnect.myID) + " disconnected.");
}

unsigned long Network::CServer::ConvertAddressToID(const sockaddr_in & aAddress)
{
	return aAddress.sin_addr.S_un.S_addr;
}
