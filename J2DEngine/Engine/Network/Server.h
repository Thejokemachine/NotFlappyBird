#pragma once
#include "ConnectionBase.h"
#include <unordered_map>

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

		void AddClient(sockaddr_in aAddress, const std::string& aName);

		sockaddr_in myLocalAddress;

		struct SClient
		{
			std::string myName;
			unsigned short myID;
		};

		std::unordered_map<unsigned long, SClient> myClients;
	};
}