#pragma once
#include <Poco/Dynamic/Struct.h>
#include "Room.h"
#include "Account.h"
#include "PacketGroup.h"

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
		};

		struct EnterRoom : public ToLobbyPacket
		{
			game::RoomId roomId;
		};
	}

	namespace from_lobby
	{
		using namespace Poco;
		using namespace Poco::Dynamic;

		enum class PacketType { ResLogin, ResRoomList, ResCreateRoom, ResEnterRoom };

		struct FromLobbyPacket
		{
			PacketType packetType;

			virtual void Write(DynamicStruct& json) const
			{
				json["packetGroup"] = (int)PacketGroup::from_lobby;
				json["packetType"] = (int)packetType;
			}
		};

		struct ResLogin : public FromLobbyPacket
		{
			account::AccountId accountId = 0;
			std::string token;

			ResLogin() { packetType = PacketType::ResLogin; }
			virtual void Write(DynamicStruct& json) const override
			{
				FromLobbyPacket::Write(json);
				json["accountId"] = accountId;
				json["token"] = token;
			}
		};

		struct ResRoomList : public FromLobbyPacket
		{
			ResRoomList() { packetType = PacketType::ResRoomList; }
		};

		struct ResCreateRoom : public FromLobbyPacket
		{
			ResCreateRoom() { packetType = PacketType::ResCreateRoom; }
		};

		struct ResEnterRoom : public FromLobbyPacket
		{
			game::RoomId roomId = 0;

			ResEnterRoom() { packetType = PacketType::ResEnterRoom; }
			virtual void Write(DynamicStruct& json) const override
			{
				FromLobbyPacket::Write(json);
				json["roomId"] = roomId;
			}
		};
	}
}