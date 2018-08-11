#pragma once
#include "CommonNetworkIncludes.h"

namespace Network
{
	class CConnectionBase
	{

	public:

		virtual void Start();
		virtual void Update();
		virtual void Stop();

	protected:

		struct SReceivedMessage
		{
			char myBuffer[MAX_BUFFER_SIZE];
			sockaddr_in myFromAddress;
		};

		SOCKET mySocket;

		CNetMessageManager myMessageManager;
		std::vector<SReceivedMessage> myReceivedBuffer;
	};
}