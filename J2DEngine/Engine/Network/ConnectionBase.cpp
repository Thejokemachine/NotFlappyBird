#include "ConnectionBase.h"
#include "Utilities/Time.h"

void Network::CConnectionBase::Start()
{
	int error = 0;
	WSADATA data = {};
	error = WSAStartup(MAKEWORD(2, 2), &data);
	if (error != 0)
	{
		PRINT("WSAStartup failed with error code: " + std::to_string(error));
		return;
	}

	PRINT("WSAStartup successful!");

	mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// Non Blocking
	unsigned long mode = 1;
	ioctlsocket(mySocket, FIONBIO, &mode);

	int bufferSize = SOCKET_BUFFER_SIZE;
	setsockopt(mySocket, SOL_SOCKET, SO_RCVBUF, (char*)&bufferSize, sizeof(bufferSize));
	setsockopt(mySocket, SOL_SOCKET, SO_SNDBUF, (char*)&bufferSize, sizeof(bufferSize));

	myMessageManager.Init(mySocket);
}

void Network::CConnectionBase::Update()
{
	myReceivedBuffer.clear();

	sockaddr_in from;
	int fromLength = sizeof(from);

	char buffer[MAX_BUFFER_SIZE];
	ZeroMemory(buffer, MAX_BUFFER_SIZE);
	Sleep(1);

	while (recvfrom(mySocket, buffer, MAX_BUFFER_SIZE, 0, (sockaddr*)&from, &fromLength) != SOCKET_ERROR)
	{
		myReceivedBuffer.push_back(SReceivedMessage());
		memcpy(&myReceivedBuffer.back().myBuffer, &buffer, MAX_BUFFER_SIZE);
		myReceivedBuffer.back().myFromAddress = from;
	}

	mySentThisSecond += myMessageManager.Flush();
	mySentTimer += CTime::GetInstance().GetDeltaTime();

	if (mySentTimer >= 1.0f)
	{
		mySentTimer = 0.f;
		PRINT(std::to_string(static_cast<float>(mySentThisSecond) / 1000.f) + "kb sent this second.");
		mySentThisSecond = 0;
	}
}

void Network::CConnectionBase::Stop()
{
}
