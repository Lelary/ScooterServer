#pragma once

#include <string>
#include <Poco/Net/SocketAcceptor.h>
#include "Account.h"

namespace Poco
{
	namespace Net
	{
		class StreamSocket;
		class SocketReactor;
	}
}

namespace network
{
	using namespace Poco::Net;
	const unsigned BUFFER_SIZE = 1024;
	struct IServer;

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
		bool Receive();

	public:
		bool Send(const char* message, int len);
		void Shutdown();

		void OnLoginSuccess(account::AccountId accountId, const std::string& token);
		void OnLoginFailure(account::AccountId accountId, const std::string& token);

	public:
		IServer* GetServer() const { return _server; }
		void SetServer(IServer* server) { _server = server; }

		account::AccountId GetAccountId() const { return _accountId; }
		void SetAccountId(account::AccountId accountId) { _accountId = accountId; }

		bool IsAuthorized() const { return _isAuthorized; }

	protected:
		std::string _peerAddress;
		SocketReactor& _reactor;
		char _receiveBuffer[BUFFER_SIZE] = { 0, };

	private:
		bool _isAuthorized;
		StreamSocket _socket;
		IServer* _server;
		account::AccountId _accountId;
	};
}