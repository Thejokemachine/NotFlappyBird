#pragma once
#include "ConnectionBase.h"
#include <unordered_map>
#include "../Graphics/Sprite.h"
#include "Utilities/TimedEvent.h"

namespace Network
{
	class CServer : public CConnectionBase
	{
	public:
		CServer() = default;
		~CServer() = default;

		void Start() override;
		void Update() override;
		void Stop() override;

	private:

		struct SClient
		{
			std::string myName;
			unsigned short myID;
			float myTimeSinceLatestPing;
			bool myConnected;

			CSprite mySprite;
		};

		void AddClient(sockaddr_in aAddress, const std::string& aName);
		void SendPlayerData();
		void ReceivePing(unsigned long aID);
		void HandleClients();
		void DisconnectClient(SClient& aClientToDisconnect);

		void SpawnPipe();

		unsigned long ConvertAddressToID(const sockaddr_in& aAddress);

		sockaddr_in myLocalAddress;

		std::unordered_map<unsigned long, SClient> myClients;

		CTimedEvent mySendPlayerDataTimer;
		CTimedEvent myPipeSpawnTimer;
	};
}