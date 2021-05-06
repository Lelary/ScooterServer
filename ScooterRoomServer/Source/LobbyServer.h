#pragma once
#include "Server.h"
#include <unordered_map>
#include <Poco/Net/SocketAcceptor.h>
#include "LobbySessionHandler.h"

namespace network
{
	class LobbyServer : public Server<LobbySessionHandler>
	{
	public:
		LobbyServer(Port port);
		bool TryLogin(account::AccountId accountId, LobbySessionHandler& session, const std::string& token);
		virtual void OnLogout(SessionHandlerBase& session) override;
		bool HandlePacket(LobbySessionHandler& session, const char* buffer);

	private:
		packet::ToLobbyPacketParser _packetParser;
		packet::ToLobbyPacketHandler _packetHandler;

	private:
		std::unordered_map<account::AccountId, LobbySessionHandler> _sessions;
	};
}