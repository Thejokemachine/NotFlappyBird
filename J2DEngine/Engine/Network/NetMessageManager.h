#pragma once
#include "CommonNetworkIncludes.h"
#include "NetMessage.h"
#include <vector>

namespace Network
{
	class CNetMessageManager
	{
	public:

		template<typename Type, typename TypeData>
		void CreateMessage(TypeData& aMessageData);

		void Init(SOCKET aSocket);
		void AddReceiver(sockaddr_in aAddress);
		unsigned int Flush();

	private:

		SOCKET mySocket;

		std::vector<CNetMessage*> myMessages;
		std::vector<sockaddr_in> myAddresses;
	};

	template<typename Type, typename TypeData>
	inline void CNetMessageManager::CreateMessage(TypeData& aMessageData)
	{
		Type* newMessage = new Type();
		newMessage->Create(aMessageData);

		myMessages.push_back(newMessage);
	}
}