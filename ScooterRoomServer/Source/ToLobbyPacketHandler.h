#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "LobbyPacket.h"
#include "ToLobbyPacketParser.h"

namespace network
{
	class LobbyServer;
	class LobbySessionHandler;
}

namespace packet
{
	class ToLobbyPacketHandler
	{
	public:
		ToLobbyPacketHandler(network::LobbyServer& lobbyServer);
		bool Handle(network::LobbySessionHandler& _session, std::unique_ptr<ToLobbyPacket> packet);

	private:
		bool OnReqLogin(network::LobbySessionHandler& session, ReqLogin* packet);
		bool OnReqRoomList(network::LobbySessionHandler& session, ReqRoomList* packet);
		bool OnCreateRoom(network::LobbySessionHandler& session, CreateRoom* packet);
		bool OnEnterRoom(network::LobbySessionHandler& session, EnterRoom* packet);

	private:
		network::LobbyServer& _lobbyServer;
	};
}