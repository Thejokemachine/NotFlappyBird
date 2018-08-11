#include "NetMessagePing.h"

void Network::CNetMessagePing::Create(SNetMessagePingData aData)
{
	myData = aData;
	myData.myType = ENetMessageType::Ping;
	CNetMessage::Create(myData);
}

Network::SNetMessagePingData & Network::CNetMessagePing::GetData()
{
	return myData;
}

void Network::CNetMessagePing::Serialize()
{
	CNetMessage::Serialize();
}

void Network::CNetMessagePing::Deserialize()
{
	CNetMessage::Deserialize();
}
