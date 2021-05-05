#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "LobbyPacket.h"
#include "ToLobbyPacketParser.h"

namespace packet
{
	class ToLobbyPacketHandler
	{
	public:
		bool Handle(std::unique_ptr<ToLobbyPacket> packet);

	private:
		bool OnReqRoomList(ReqRoomList* packet);
		bool OnCreateRoom(CreateRoom* packet);
		bool OnEnterRoom(EnterRoom* packet);
	};

	void example();
}