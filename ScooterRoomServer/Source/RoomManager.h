#pragma once

#include <memory>
#include <queue>
#include <thread>
#include <unordered_map>
#include "Server.h"
#include "Account.h"
#include "Room.h"

namespace game
{
	class RoomManager
	{
		static const int MAX_ROOM_COUNT = 10;
		static const int MAX_USER_COUNT = 5;

	public:
		RoomManager(network::Port createRoomPort, network::Port roomPortStart);
		bool TryGetPort(int roomNo, network::Port& outPort) const;
		std::unique_ptr<Room> Create(account::AccountId roomOwner);
		std::unique_ptr<Room> Run(std::unique_ptr<Room> ptr);

	private:
		const network::Port CREATE_ROOM_PORT;
		const network::Port ROOM_PORT_START;

		std::queue<network::Port> _unoccupiedPorts;
		std::unordered_map<RoomId, Room> _rooms;
	};
}