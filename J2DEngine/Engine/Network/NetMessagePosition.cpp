#include "NetMessagePosition.h"

// You need to set the type manually before creating
void Network::CNetMessagePosition::Create(SNetMessagePositionData aData)
{
	myData = aData;
	CNetMessage::Create(myData);
}

Network::SNetMessagePositionData & Network::CNetMessagePosition::GetData()
{
	return myData;
}

void Network::CNetMessagePosition::Serialize()
{
	CNetMessage::Serialize();
	SERIALIZE(myBuffer, myData.myPosition.x);
	SERIALIZE(myBuffer, myData.myPosition.y);
}

void Network::CNetMessagePosition::Deserialize()
{
	CNetMessage::Deserialize();
	DESERIALIZE(myBuffer, myData.myPosition.x);
	DESERIALIZE(myBuffer, myData.myPosition.y);
}
