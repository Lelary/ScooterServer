#pragma once
#include "SessionHandlerBase.h"

namespace network
{
	class LobbySessionHandler : public SessionHandlerBase
	{
	public:
		LobbySessionHandler(StreamSocket& socket, SocketReactor& reactor);
		virtual void OnReadable(ReadableNotification* pNotification) override;
	};
}