#include "ToLobbyPacketParser.h"
#include <string>
#include "PacketGroup.h"

namespace packet
{

	std::unique_ptr<ToLobbyPacket> ToLobbyPacketParser::Parse(const std::string& buffer)
	{
		PacketType refPacketType;
		auto ptr = Parse(buffer, refPacketType);
		if (ptr == nullptr)
			return nullptr;

		ptr->packetType = refPacketType;
		return ptr;
	}

	std::unique_ptr<ToLobbyPacket> ToLobbyPacketParser::Parse(const std::string& buffer, PacketType& refPacketType)
	{
		try
		{
			Var result = _parser.parse(buffer);
			Object::Ptr object = result.extract<Object::Ptr>();

			int packetGroup = object->getValue<int>("packetGroup");
			if (packetGroup != (int)PacketGroup::to_lobby)
				return nullptr;

			int packetType = object->getValue<int>("packetType");
			refPacketType = (PacketType)packetType;

			switch ((PacketType)packetType)
			{
			case PacketType::ReqLogin:
				return ParseReqLogin(object);
			case PacketType::ReqRoomList:
				return ParseReqRoomList(object);
			case PacketType::CreateRoom:
				return ParseCreateRoom(object);
			case PacketType::EnterRoom:
				return ParseEnterRoom(object);
			default:
				break;
			}
		}

		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		return nullptr;
	}

	std::unique_ptr<ToLobbyPacket> ToLobbyPacketParser::ParseReqLogin(Object::Ptr object)
	{
		auto packet = std::make_unique<ReqLogin>();

		account::AccountId accountId = object->getValue<account::AccountId>("accountId");
		packet->accountId = accountId;

		std::string token = object->getValue<std::string>("token");
		packet->token = token;

		return packet;
	}

	std::unique_ptr<ToLobbyPacket> ToLobbyPacketParser::ParseReqRoomList(Object::Ptr object)
	{
		return std::make_unique<ReqRoomList>();
	}

	std::unique_ptr<ToLobbyPacket> ToLobbyPacketParser::ParseCreateRoom(Object::Ptr object)
	{
		auto packet = std::make_unique<CreateRoom>();
		return packet;
	}

	std::unique_ptr<ToLobbyPacket> ToLobbyPacketParser::ParseEnterRoom(Object::Ptr object)
	{
		game::RoomId roomId = object->getValue<game::RoomId>("roomId");

		auto packet = std::make_unique<EnterRoom>();
		packet->roomId = roomId;
		return packet;
	}
}