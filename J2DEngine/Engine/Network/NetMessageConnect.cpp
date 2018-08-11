#include "NetMessageConnect.h"

void Network::CNetMessageConnect::Create(SNetMessageConnectData aData)
{
	myData = aData;
	myData.myType = ENetMessageType::Connect;
	CNetMessage::Create(myData);
}

Network::SNetMessageConnectData & Network::CNetMessageConnect::GetData()
{
	return myData;
}

void Network::CNetMessageConnect::Serialize()
{
	CNetMessage::Serialize();
	SERIALIZE(myBuffer, myData.myName);
}

void Network::CNetMessageConnect::Deserialize()
{
	CNetMessage::Deserialize();
	DESERIALIZE(myBuffer, myData.myName);
}
