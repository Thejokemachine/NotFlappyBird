#pragma once
#include "NetMessage.h"
#include "../Math/Vector2.h"

namespace Network
{
	struct SNetMessagePositionData : SNetMessageData
	{
		CVector2f myPosition;
	};

	class CNetMessagePosition: public CNetMessage
	{
	public:
		void Create(SNetMessagePositionData aData);
		SNetMessagePositionData& GetData();

	private:
		virtual void Serialize() override;
		virtual void Deserialize() override;

		SNetMessagePositionData myData;
	};
}