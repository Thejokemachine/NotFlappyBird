#include "NetMessagePlayerData.h"

void Network::CNetMessagePlayerData::Create(SNetMessagePlayerDataData aData)
{
	myData = aData;
	myData.myType = ENetMessageType::PlayerData;
	CNetMessage::Create(myData);
}

Network::SNetMessagePlayerDataData & Network::CNetMessagePlayerData::GetData()
{
	return myData;
}

void Network::CNetMessagePlayerData::Serialize()
{
	CNetMessage::Serialize();
	SERIALIZE(myBuffer, myData.myPosition);
	SERIALIZE(myBuffer, myData.myRotation);
}

void Network::CNetMessagePlayerData::Deserialize()
{
	CNetMessage::Deserialize();
	DESERIALIZE(myBuffer, myData.myPosition);
	DESERIALIZE(myBuffer, myData.myRotation);
}
