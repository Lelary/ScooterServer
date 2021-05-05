#include "RoomSessionHandler.h"

namespace network
{
	RoomSessionHandler::RoomSessionHandler(StreamSocket& socket, SocketReactor& reactor)
		:SessionHandlerBase(socket, reactor)
	{

	}
	void RoomSessionHandler::OnReadable(ReadableNotification* pNotification)
	{
		pNotification->release();

		try
		{
			const unsigned BUFFER_SIZE = 256;
			char buffer[BUFFER_SIZE] = { 0, };
			int n = _socket.receiveBytes(buffer, sizeof(buffer));

			if (n > 0)
			{
				char szSendMessage[BUFFER_SIZE] = { 0, };
				sprintf_s(szSendMessage, BUFFER_SIZE - 1, "Re:%s", buffer);
				int msgLen = strnlen_s(szSendMessage, BUFFER_SIZE - 1);

				_socket.sendBytes(szSendMessage, msgLen);

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
			std::cout << "EchoServer : " << e.displayText() << std::endl;

			_socket.shutdown();

			delete this;
		}
	}
}