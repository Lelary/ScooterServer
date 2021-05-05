#include "Room.h"

namespace game
{
	Room::Room(account::AccountId roomOwner, int maxUserCount)
		:_roomOwner(roomOwner), _maxUserCount(maxUserCount)
	{
		_participants.push_back(roomOwner);
	}

	bool Room::Initialize(network::Port port)
	{
		if (_server != nullptr)
			return false;

		_server = std::make_unique<network::RoomServer>(port);
		return _server->Initialize();
	}

	void Room::Run()
	{
		_server->Run();
	}

	network::Port Room::GetPort() const
	{
		if (_server == nullptr)
			return network::PORT_NONE;

		return _server->GetPort();
	}
}