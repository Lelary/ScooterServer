#pragma once
#include "Room.h"
#include "Account.h"

namespace packet
{
	namespace to_lobby
	{
		enum class PacketType { ReqLogin, ReqRoomList, CreateRoom, EnterRoom };

		struct ToLobbyPacket
		{
			PacketType packetType;
			
		};

		struct ReqLogin : public ToLobbyPacket
		{
			account::AccountId accountId;
			std::string token;
		};

		struct ReqRoomList : public ToLobbyPacket
		{
		};

		struct CreateRoom : public ToLobbyPacket
		{
//			account::AccountId accountId;
		};
		
		struct EnterRoom : public ToLobbyPacket
		{
			game::RoomId roomId;
//			account::AccountId accountId;
		};
	}
}