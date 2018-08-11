#include "NetMessageChat.h"

namespace Network
{
	void CNetMessageChat::Create(SNetMessageChatData aData)
	{
		myData = aData;
		myData.myType = ENetMessageType::Chat;
		CNetMessage::Create(myData);
	}

	SNetMessageChatData & CNetMessageChat::GetData()
	{
		return myData;
	}

	void CNetMessageChat::Serialize()
	{
		CNetMessage::Serialize();
		SERIALIZE(myBuffer, myData.myMessage);
	}

	void CNetMessageChat::Deserialize()
	{
		CNetMessage::Deserialize();
		DESERIALIZE(myBuffer, myData.myMessage);
	}
}