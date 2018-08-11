#pragma once
#include "ConnectionBase.h"

class CGame;

namespace Network
{
	class CClient : public CConnectionBase
	{
	public:
		CClient() = default;
		~CClient() = default;

		void Start() override;
		void Update() override;
		void Stop() override;

		void BindGame(CGame& aGame);

	private:
		sockaddr_in myLocalAddress;
		sockaddr_in myServerAddress;

		CGame* myGamePtr;
	};
}