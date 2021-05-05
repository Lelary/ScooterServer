#pragma once
#include "Server.h"
#include "RoomSessionHandler.h"

namespace network
{
	class RoomServer : public Server<RoomSessionHandler>
	{
	public:
		RoomServer(Port port);
	};
}