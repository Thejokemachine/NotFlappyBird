#pragma once
#include "NetMessage.h"
#include "../Engine/SmallString.h"

namespace Network
{
	struct SNetMessageChatData : SNetMessageData
	{
		CSmallString myMessage;
	};

	class CNetMessageChat : public CNetMessage
	{
	public:
		void Create(SNetMessageChatData aData);
		SNetMessageChatData& GetData();

	private:
		virtual void Serialize() override;
		virtual void Deserialize() override;

		SNetMessageChatData myData;
	};
}