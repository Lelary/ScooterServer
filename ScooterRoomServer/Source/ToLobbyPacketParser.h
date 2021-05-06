#pragma once
#include <memory>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include "LobbyPacket.h"

namespace packet
{
	using namespace Poco;
	using namespace Poco::JSON;
	using namespace Poco::Dynamic;
	using namespace to_lobby;

	class ToLobbyPacketParser
	{
	public:
		std::unique_ptr<ToLobbyPacket> Parse(const std::string& buffer);

	private:
		std::unique_ptr<ToLobbyPacket> Parse(const std::string& buffer, PacketType& refPacketType);
		std::unique_ptr<ToLobbyPacket> ParseReqLogin(Object::Ptr object);
		std::unique_ptr<ToLobbyPacket> ParseReqRoomList(Object::Ptr object);
		std::unique_ptr<ToLobbyPacket> ParseCreateRoom(Object::Ptr object);
		std::unique_ptr<ToLobbyPacket> ParseEnterRoom(Object::Ptr object);

	private:
		Parser _parser;
	};
}