#pragma once

#include <string>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketAcceptor.h>
#include <Poco/Net/ParallelSocketAcceptor.h>

namespace network
{
	using namespace Poco::Net;
	const unsigned BUFFER_SIZE = 1024;

	class SessionHandlerBase
	{
	public:
		SessionHandlerBase(StreamSocket& socket, SocketReactor& reactor);
		virtual ~SessionHandlerBase();
		virtual void OnReadable(ReadableNotification* pNotification) = 0;
		// 		virtual void OnError(ReadableNotification* pNotification) = 0;
		// 		virtual void OnIdle(ReadableNotification* pNotification) = 0;
		// 		virtual void OnShutdown(ReadableNotification* pNotification) = 0;
		// 		virtual void OnTimeout(ReadableNotification* pNotification) = 0;
		// 		virtual void OnWritable(ReadableNotification* pNotification) = 0;

	protected:
		bool Receive()
		{
			ZeroMemory(_receiveBuffer, BUFFER_SIZE);

			int n = _socket.receiveBytes(_receiveBuffer, sizeof(_receiveBuffer));
			return (n > 0);
		}

		bool Send(const char* message, int len)
		{
			if (len >= BUFFER_SIZE)
			{
				std::cout << "error" << std::endl;
				return false;
			}

			char sendBuffer[BUFFER_SIZE] = { 0, };
			strncpy_s(sendBuffer, message, len);
			_socket.sendBytes(sendBuffer, len);
			return true;
		}

		void Shutdown()
		{
			_socket.shutdown();
		}

	protected:
		std::string _peerAddress;
		SocketReactor& _reactor;
		char _receiveBuffer[BUFFER_SIZE] = { 0, };

	private:
		StreamSocket _socket;
	};
}