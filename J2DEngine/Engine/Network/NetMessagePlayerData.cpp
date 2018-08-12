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
	SERIALIZE(myBuffer, myData.myPosition.x);
	SERIALIZE(myBuffer, myData.myPosition.y);
	SERIALIZE(myBuffer, myData.myRotation);
}

void Network::CNetMessagePlayerData::Deserialize()
{
	CNetMessage::Deserialize();
	DESERIALIZE(myBuffer, myData.myPosition.x);
	DESERIALIZE(myBuffer, myData.myPosition.y);
	DESERIALIZE(myBuffer, myData.myRotation);
}
