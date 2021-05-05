#include "LobbySessionHandler.h"
#include "ToLobbyPacketParser.h"
#include "ToLobbyPacketHandler.h"

namespace network
{
	LobbySessionHandler::LobbySessionHandler(StreamSocket& socket, SocketReactor& reactor)
		:SessionHandlerBase(socket, reactor)
	{

	}

	void LobbySessionHandler::OnReadable(ReadableNotification* pNotification)
	{
		if (!_OnReadable(pNotification))
		{
			Shutdown();
			delete this;
		}
	}

	bool LobbySessionHandler::_OnReadable(ReadableNotification* pNotification)
	{
		pNotification->release();

		try
		{
			if (!Receive())
				return false;

			std::cout << "message : " << _receiveBuffer << std::endl;

			auto packet = _packetParser.Parse(_receiveBuffer);
			if (!_packetHandler.Handle(std::move(packet)))
				return false;

			return true;
		}
		catch (const Poco::Exception& e)
		{
			return false;
		}
	}
}