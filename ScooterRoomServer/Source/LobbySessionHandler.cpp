#include "LobbySessionHandler.h"
#include "ToLobbyPacketParser.h"
#include "ToLobbyPacketHandler.h"
#include "LobbyServer.h"

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

			if (!GetLobbyServer()->HandlePacket(*this, _receiveBuffer))
				return false;

			return true;
		}
		catch (const Poco::Exception& e)
		{
			return false;
		}
	}

	LobbyServer* LobbySessionHandler::GetLobbyServer()
	{
		return static_cast<LobbyServer*>(GetServer());
	}
}