#pragma once
#include "NetMessage.h"

namespace Network
{
	struct SNetMessagePingData : SNetMessageData
	{
	};

	class CNetMessagePing : public CNetMessage
	{
	public:
		void Create(SNetMessagePingData aData);
		SNetMessagePingData& GetData();

	private:
		virtual void Serialize() override;
		virtual void Deserialize() override;

		SNetMessagePingData myData;
	};
}