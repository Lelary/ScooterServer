#include <memory>
#include <string>
#include "ToLobbyPacketHandler.h"
#include "LobbySessionHandler.h"

namespace packet
{
	bool ToLobbyPacketHandler::Handle(network::LobbySessionHandler& session, std::unique_ptr<ToLobbyPacket> packet)
	{
		if (packet == nullptr)
			return false;

		switch (packet->packetType)
		{
		case PacketType::ReqRoomList:
			return OnReqRoomList(session, static_cast<ReqRoomList*>(packet.get()));
		case PacketType::CreateRoom:
			return OnCreateRoom(session, static_cast<CreateRoom*>(packet.get()));
		case PacketType::EnterRoom:
			return OnEnterRoom(session, static_cast<EnterRoom*>(packet.get()));
		default:
			break;
		}

		return false;
	}

	bool ToLobbyPacketHandler::OnReqRoomList(network::LobbySessionHandler& session, ReqRoomList* packet)
	{
		//const char* msg = "";
		//session.Send(msg, strnlen_s(msg, network::BUFFER_SIZE));
		return true;
	}

	bool ToLobbyPacketHandler::OnCreateRoom(network::LobbySessionHandler& session, CreateRoom* packet)
	{
		return true;
	}

	bool ToLobbyPacketHandler::OnEnterRoom(network::LobbySessionHandler& session, EnterRoom* packet)
	{
		std::cout << packet->accountId << std::endl;
		return true;
	}
}