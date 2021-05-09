#include <memory>
#include <string>
#include "ToLobbyPacketHandler.h"
#include "LobbySessionHandler.h"
#include "LobbyServer.h"

namespace packet
{
	ToLobbyPacketHandler::ToLobbyPacketHandler(network::LobbyServer& lobbyServer)
		:_lobbyServer(lobbyServer)
	{
	}

	bool ToLobbyPacketHandler::Handle(network::LobbySessionHandler& session, std::unique_ptr<ToLobbyPacket> packet)
	{
		if (packet == nullptr)
			return false;

		switch (packet->packetType)
		{
		case PacketType::ReqLogin:
			return OnReqLogin(session, static_cast<ReqLogin*>(packet.get()));
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

	bool ToLobbyPacketHandler::OnReqLogin(network::LobbySessionHandler& session, ReqLogin* packet)
	{
		if (!_lobbyServer.TryLogin(packet->accountId, session, packet->token))
		{
			session.OnLoginFailure(packet->accountId, packet->token);
			return false;
		}

		session.OnLoginSuccess(packet->accountId, packet->token);

		packet::from_lobby::ResLogin outPacket;
		outPacket.accountId = packet->accountId;
		session.Send(outPacket);

		return true;
	}

	bool ToLobbyPacketHandler::OnReqRoomList(network::LobbySessionHandler& session, ReqRoomList* packet)
	{
		packet::from_lobby::ResRoomList outPacket;
		session.Send(outPacket);

		return true;
	}

	bool ToLobbyPacketHandler::OnCreateRoom(network::LobbySessionHandler& session, CreateRoom* packet)
	{
		packet::from_lobby::ResCreateRoom outPacket;
		session.Send(outPacket);

		return true;
	}

	bool ToLobbyPacketHandler::OnEnterRoom(network::LobbySessionHandler& session, EnterRoom* packet)
	{
		packet::from_lobby::ResEnterRoom outPacket;
		outPacket.roomId = packet->roomId;
		session.Send(outPacket);

		return true;
	}
}