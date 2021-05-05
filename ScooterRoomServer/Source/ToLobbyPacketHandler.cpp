#include <memory>
#include <string>
#include "ToLobbyPacketHandler.h"

namespace packet
{
	bool ToLobbyPacketHandler::Handle(std::unique_ptr<ToLobbyPacket> packet)
	{
		if (packet == nullptr)
			return false;

		switch (packet->packetType)
		{
		case PacketType::ReqRoomList:
			return OnReqRoomList(static_cast<ReqRoomList*>(packet.get()));
		case PacketType::CreateRoom:
			return OnCreateRoom(static_cast<CreateRoom*>(packet.get()));
		case PacketType::EnterRoom:
			return OnEnterRoom(static_cast<EnterRoom*>(packet.get()));
		default:
			break;
		}

		return false;
	}

	bool ToLobbyPacketHandler::OnReqRoomList(ReqRoomList* packet)
	{
		return true;
	}

	bool ToLobbyPacketHandler::OnCreateRoom(CreateRoom* packet)
	{
		return true;
	}

	bool ToLobbyPacketHandler::OnEnterRoom(EnterRoom* packet)
	{
		std::cout << packet->accountId << std::endl;
		return true;
	}

	void example()
	{
		std::string _sampleJson = "{ \"packetGroup\" : 0, \"packetType\" : 2, \"accountId\" : 12345, \"roomId\" : 10 }";

		ToLobbyPacketParser packetParser;
		std::unique_ptr<ToLobbyPacket> packet = packetParser.Parse(_sampleJson);

		ToLobbyPacketHandler packetHandler;
		packetHandler.Handle(std::move(packet));
	}
}