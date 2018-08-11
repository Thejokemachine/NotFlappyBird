#pragma once
#include "NetMessage.h"
#include "../Engine/SmallString.h"

namespace Network
{
	struct SNetMessageConnectData : SNetMessageData
	{
		CSmallString myName;
	};

	class CNetMessageConnect : public CNetMessage
	{
	public:
		void Create(SNetMessageConnectData aData);
		SNetMessageConnectData& GetData();

	private:
		virtual void Serialize() override;
		virtual void Deserialize() override;

		SNetMessageConnectData myData;
	};
}