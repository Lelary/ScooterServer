#pragma once

#include <memory>
#include <vector>
#include "Server.h"
#include "Account.h"
#include "RoomServer.h"

namespace game
{
	using RoomNo = unsigned __int64;

	class Room
	{
	public:
		Room(account::AccountId roomOwner, int maxUserCount);
		bool Initialize(network::Port port);
		void Run();

		network::Port GetPort() const;

	private:
		const account::AccountId _roomOwner;
		const int _maxUserCount;
		std::vector<account::AccountId> _participants;

		std::unique_ptr<network::RoomServer> _server;
	};
}