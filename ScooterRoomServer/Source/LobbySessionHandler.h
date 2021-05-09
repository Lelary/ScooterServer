#pragma once
#include "SessionHandlerBase.h"
#include "ToLobbyPacketParser.h"
#include "ToLobbyPacketHandler.h"
#include "FromLobbyPacketWriter.h"

namespace network
{
	class LobbyServer;
}

namespace packet
{
	namespace from_lobby
	{
		struct FromLobbyPacket;
	}
}

namespace network
{
	class LobbySessionHandler : public SessionHandlerBase
	{
	public:
		using SessionHandlerBase::Send;
	public:
		LobbySessionHandler(StreamSocket& socket, SocketReactor& reactor);
		virtual void OnReadable(ReadableNotification* pNotification) override;
		bool Send(const packet::from_lobby::FromLobbyPacket& packet);
	private:
		bool _OnReadable(ReadableNotification* pNotification);
		LobbyServer* GetLobbyServer();
		packet::FromLobbyPacketWriter _writer;

	};
}