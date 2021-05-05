#pragma once

#include <string>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketAcceptor.h>
#include <Poco/Net/ParallelSocketAcceptor.h>

namespace network
{
	using namespace Poco::Net;

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
		std::string _peerAddress;
		StreamSocket _socket;
		SocketReactor& _reactor;
	};
}