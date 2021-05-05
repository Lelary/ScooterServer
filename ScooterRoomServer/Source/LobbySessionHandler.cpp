#include "LobbySessionHandler.h"

namespace network
{
	LobbySessionHandler::LobbySessionHandler(StreamSocket& socket, SocketReactor& reactor)
		:SessionHandlerBase(socket, reactor)
	{

	}

	void LobbySessionHandler::OnReadable(ReadableNotification* pNotification)
	{
		pNotification->release();

		try
		{
			const unsigned BUFFER_SIZE = 256;
			char buffer[BUFFER_SIZE] = { 0, };
			int n = _socket.receiveBytes(buffer, sizeof(buffer));

			if (n > 0)
			{
				std::cout << "message : " << buffer << std::endl;
			}
			else
			{
				_socket.shutdown();
				delete this;
			}
		}
		catch (const Poco::Exception& e)
		{
			_socket.shutdown();

			delete this;
		}
	}
}