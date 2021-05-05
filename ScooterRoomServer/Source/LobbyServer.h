#pragma once
#include "Server.h"
#include "LobbySessionHandler.h"

namespace network
{
	class LobbyServer : public Server<LobbySessionHandler>
	{
	public:
		LobbyServer(Port port);
	};
}