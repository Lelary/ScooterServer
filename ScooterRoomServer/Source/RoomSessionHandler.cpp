#include "RoomSessionHandler.h"

namespace network
{
	RoomSessionHandler::RoomSessionHandler(StreamSocket& socket, SocketReactor& reactor)
		:SessionHandlerBase(socket, reactor)
	{

	}

	void RoomSessionHandler::OnReadable(ReadableNotification* pNotification)
	{
		if (!_OnReadable(pNotification))
		{
			Shutdown();
			delete this;
		}
	}

	bool RoomSessionHandler::_OnReadable(ReadableNotification* pNotification)
	{
		pNotification->release();

		try
		{
			if (!Receive())
				return false;

			char message[BUFFER_SIZE] = { 0, };
			sprintf_s(message, BUFFER_SIZE - 1, "Re:%s", _receiveBuffer);
			if (!Send(message, strnlen_s(message, BUFFER_SIZE)))
				return false;

			std::cout << "message : " << message << std::endl;
			return true;
		}
		catch (const Poco::Exception& e)
		{
			std::cout << "EchoServer : " << e.displayText() << std::endl;
			return false;
		}
	}
}