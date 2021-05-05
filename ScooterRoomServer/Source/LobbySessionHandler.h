#pragma once
#include "SessionHandlerBase.h"
#include "ToLobbyPacketParser.h"
#include "ToLobbyPacketHandler.h"

namespace network
{
	class LobbySessionHandler : public SessionHandlerBase
	{
	public:
		LobbySessionHandler(StreamSocket& socket, SocketReactor& reactor);
		virtual void OnReadable(ReadableNotification* pNotification) override;
	private:
		bool _OnReadable(ReadableNotification* pNotification);

		packet::ToLobbyPacketParser _packetParser;
		packet::ToLobbyPacketHandler _packetHandler;
	};
}