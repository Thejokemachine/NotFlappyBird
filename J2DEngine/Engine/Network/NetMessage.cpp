#include "NetMessage.h"

namespace Network
{
	void CNetMessage::Create(SNetMessageData aData)
	{
		myData = aData;
	}

	SNetMessageData& CNetMessage::GetBaseData()
	{
		return myData;
	}

	void CNetMessage::Pack()
	{
		Serialize();
	}

	void CNetMessage::Unpack()
	{
		Deserialize();
	}

	void CNetMessage::ReceiveData(char * aData, short aSize)
	{
		myBuffer.resize(aSize);
		memcpy(&myBuffer[0], aData, aSize);
	}

	size_t CNetMessage::GetBufferSize()
	{
		return sizeof(myBuffer);
	}

	char* CNetMessage::GetBufferStart()
	{
		return &myBuffer[0];
	}

	void CNetMessage::Serialize()
	{
		SERIALIZE(myBuffer, myData.myType);
		SERIALIZE(myBuffer, myData.myID);
	}

	void CNetMessage::Deserialize()
	{
		DESERIALIZE(myBuffer, myData.myType);
		DESERIALIZE(myBuffer, myData.myID);
	}
}