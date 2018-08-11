#pragma once
#include "SerializeHelper.h"
#include "NetMessageTypes.h"
#include <vector>


#define SERIALIZE(aStream, aType) serialize(aType, aStream)
#define DESERIALIZE(aStream, aType) aType = deserialize<decltype(aType)>(aStream)

namespace Network
{
	struct SNetMessageData
	{
		ENetMessageType myType = ENetMessageType::Base;
		unsigned int myTimeStamp = 0;
		short myID = 0;
		short myTargetID = 0;
	};

	class CNetMessage
	{
	public:

		void Create(SNetMessageData aData);
		SNetMessageData& GetBaseData();

		void Pack();
		void Unpack();

		void ReceiveData(char* aData, short aSize);

		size_t GetBufferSize();
		char* GetBufferStart();

	protected:

		virtual void Serialize();
		virtual void Deserialize();

		std::vector<char> myBuffer;
		SNetMessageData myData;
	};
}