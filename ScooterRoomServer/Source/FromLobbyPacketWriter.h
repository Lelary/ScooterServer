#pragma once
#include "LobbyPacket.h"

namespace packet
{
	class FromLobbyPacketWriter
	{
	public:
		std::string Write(const packet::from_lobby::FromLobbyPacket& packet);
	};
}