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

 			if (!HandlePacket(*this, _receiveBuffer))
 				return false;

			return true;
		}
		catch (const Poco::Exception& e)
		{
			return false;
		}
	}

	bool LobbySessionHandler::HandlePacket(LobbySessionHandler& session, const char* buffer)
	{
		auto packet = _packetParser.Parse(buffer);
		if (packet == nullptr)
			return false;

		if (!_packetHandler.Handle(session, std::move(packet)))
			return false;

		return true;
	}
}