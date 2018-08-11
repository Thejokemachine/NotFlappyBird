#pragma once
#include "NetMessage.h"
#include "../Engine/SmallString.h"
#include "../Math/Vector2.h"

namespace Network
{
	struct SNetMessagePlayerDataData : SNetMessageData
	{
		CVector2f myPosition;
		float myRotation;
	};

	class CNetMessagePlayerData : public CNetMessage
	{
	public:
		void Create(SNetMessagePlayerDataData aData);
		SNetMessagePlayerDataData& GetData();

	private:
		virtual void Serialize() override;
		virtual void Deserialize() override;

		SNetMessagePlayerDataData myData;
	};
}