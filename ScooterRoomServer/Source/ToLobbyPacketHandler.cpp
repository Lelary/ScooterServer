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

		std::stringstream ss;
		ss << "welcome " << session.GetAccountId();

		std::string msg = ss.str();
		session.Send(msg.c_str(), msg.length());

		return true;
	}

	bool ToLobbyPacketHandler::OnReqRoomList(network::LobbySessionHandler& session, ReqRoomList* packet)
	{
		std::stringstream ss;
		ss << "you " << session.GetAccountId() << " requested to give room list";

		std::string msg = ss.str();
		session.Send(msg.c_str(), msg.length());

		return true;
	}

	bool ToLobbyPacketHandler::OnCreateRoom(network::LobbySessionHandler& session, CreateRoom* packet)
	{
		std::stringstream ss;
		ss << "you " << session.GetAccountId() << " requested to create new room";

		std::string msg = ss.str();
		session.Send(msg.c_str(), msg.length());

		return true;
	}

	bool ToLobbyPacketHandler::OnEnterRoom(network::LobbySessionHandler& session, EnterRoom* packet)
	{
		std::cout << packet->roomId << std::endl;

		std::stringstream ss;
		ss << "you " << session.GetAccountId() << " requested to enter room number " << packet->roomId;

		std::string msg = ss.str();
		session.Send(msg.c_str(), msg.length());

		return true;
	}
}