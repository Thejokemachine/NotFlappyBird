#pragma once

namespace Network
{
	enum class ENetMessageType
	{
		Base,
		Chat,
		Ping,
		Connect,
		NewPlayer,
		PlayerData,
		NewPipe
	};
}