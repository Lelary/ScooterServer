#include "RoomManager.h"

namespace game
{
	RoomManager::RoomManager(network::Port createRoomPort, network::Port roomPortStart)
		:CREATE_ROOM_PORT(createRoomPort), ROOM_PORT_START(roomPortStart)
	{
		for (int i = 0; i < MAX_ROOM_COUNT; i++)
		{
			_unoccupiedPorts.push(roomPortStart + i);
		}
	}

	bool RoomManager::TryGetPort(int roomNo, network::Port& outPort) const
	{
		outPort = network::PORT_NONE;

		auto foundIter = _rooms.find(roomNo);
		if (foundIter == _rooms.end())
			return false;

		const auto& room = foundIter->second;
		outPort = room.GetPort();
		if (outPort == network::PORT_NONE)
			return false;

		return true;
	}

	std::unique_ptr<Room> RoomManager::Create(account::AccountId roomOwner)
	{
		if (_unoccupiedPorts.empty())
		{
			std::cout << "error ";
			return nullptr;
		}

		network::Port port = _unoccupiedPorts.front();
		_unoccupiedPorts.pop();

		auto room = std::make_unique<Room>(roomOwner, MAX_USER_COUNT);
		room->Initialize(port);
		return room;
	}

	std::unique_ptr<Room> RoomManager::Run(std::unique_ptr<Room> ptr)
	{
		ptr->Run();
		//...
		return std::move(ptr);
	}

}