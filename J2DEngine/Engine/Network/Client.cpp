#include "Client.h"
#include "NetMessageChat.h"
#include "../Game/Game.h"
#include "Utilities/Time.h"

void Network::CClient::Start()
{
	PRINT("Starting up client...");
	CConnectionBase::Start();

	myLocalAddress.sin_family = AF_INET;
	myLocalAddress.sin_port = 0;
	myLocalAddress.sin_addr.s_addr = INADDR_ANY;

	int error = bind(mySocket, (sockaddr*)&myLocalAddress, sizeof(myLocalAddress));
	if (error != 0)
	{
		PRINT("Binding of local address failed with error code: " + std::to_string(error));
		return;
	}

	std::string serverIP = "88.83.34.36";
	unsigned short port = 54000;

	inet_pton(AF_INET, serverIP.c_str(), &myServerAddress.sin_addr.s_addr);
	myServerAddress.sin_port = htons(port);
	myServerAddress.sin_family = AF_INET;

	myMessageManager.AddReceiver(myServerAddress);

	SNetMessageConnectData message;
	message.myID = 1337;
	message.myTargetID = 0;
	message.myName = "Joakim";

	myMessageManager.CreateMessage<CNetMessageConnect>(message);
}

void Network::CClient::Update()
{
	CConnectionBase::Update();

	SendPlayerData();
	myPingTimer += CTime::GetInstance().GetDeltaTime();
	if (myPingTimer > FREQ_PING)
	{
		myPingTimer = 0.f;
		PingServer();
	}

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
			PRINT("Received ping from server");
			break;
		}
		case Network::ENetMessageType::Connect:
		{
			CNetMessageConnect msg;
			msg.ReceiveData(buffer, sizeof(SNetMessageConnectData));
			msg.Unpack();
			PRINT("Connected to " + msg.GetData().myName.ToString());
			break;
		}
		case ENetMessageType::NewPlayer:
		{
			CNetMessage msg;
			msg.ReceiveData(buffer, sizeof(SNetMessageData));
			msg.Unpack();

			myGamePtr->AddOtherPlayer(msg.GetBaseData().myID);
			PRINT("Added a player with ID: " + std::to_string(msg.GetBaseData().myID));
			break;
		}
		case ENetMessageType::PlayerData:
		{
			CNetMessagePlayerData msg;
			msg.ReceiveData(buffer, sizeof(SNetMessagePlayerDataData));
			msg.Unpack();

			myGamePtr->UpdateOtherPlayer(msg.GetBaseData().myID, msg.GetData().myPosition, msg.GetData().myRotation);
		}
		}
	}
}

void Network::CClient::Stop()
{
	CConnectionBase::Stop();
}

void Network::CClient::BindGame(CGame& aGame)
{
	myGamePtr = &aGame;
}

void Network::CClient::SendPlayerData()
{
	SNetMessagePlayerDataData data;
	data.myPosition = myGamePtr->GetPlayer().GetSprite().GetPosition();
	data.myRotation = myGamePtr->GetPlayer().GetSprite().GetRotation();
	data.myTargetID = 0;

	myMessageManager.CreateMessage<CNetMessagePlayerData>(data);
}

void Network::CClient::PingServer()
{
	SNetMessageData ping;
	ping.myTargetID = 0;
	ping.myType = ENetMessageType::Ping;

	myMessageManager.CreateMessage<CNetMessage>(ping);
}
