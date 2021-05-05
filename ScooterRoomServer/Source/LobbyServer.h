#pragma once
#include "Server.h"
#include <Poco/Net/SocketAcceptor.h>
#include "LobbySessionHandler.h"

namespace network
{
	class LobbyServer : public Server<LobbySessionHandler>
	{
	public:
		LobbyServer(Port port);
// 		bool HandlePacket(LobbySessionHandler& session, const char* buffer);
// 	private:
// 		packet::ToLobbyPacketParser _packetParser;
// 		packet::ToLobbyPacketHandler _packetHandler;
	};
}