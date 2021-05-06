#include "SessionHandlerBase.h"
#include "IServer.h"

namespace network
{
	SessionHandlerBase::SessionHandlerBase(StreamSocket& socket, SocketReactor& reactor)
		: _socket(socket), _reactor(reactor)
	{
		_peerAddress = socket.peerAddress().toString();

		std::cout << "connection from " << _peerAddress << " ..." << std::endl;

		_reactor.addEventHandler(_socket, Poco::Observer<SessionHandlerBase, ReadableNotification>(*this, &SessionHandlerBase::OnReadable));
		// 		_reactor.addEventHandler(_socket, Poco::Observer<SessionHandlerBase, ErrorNotification>(*this, &SessionHandlerBase::OnError));
		// 		_reactor.addEventHandler(_socket, Poco::Observer<SessionHandlerBase, IdleNotification>(*this, &SessionHandlerBase::OnIdle));
		// 		_reactor.addEventHandler(_socket, Poco::Observer<SessionHandlerBase, ShutdownNotification>(*this, &SessionHandlerBase::OnShutdown));
		// 		_reactor.addEventHandler(_socket, Poco::Observer<SessionHandlerBase, TimeoutNotification>(*this, &SessionHandlerBase::OnTimeout));
		// 		_reactor.addEventHandler(_socket, Poco::Observer<SessionHandlerBase, WritableNotification>(*this, &SessionHandlerBase::OnWritable));
	}

	SessionHandlerBase::~SessionHandlerBase()
	{
		std::cout << "disconnected " << _peerAddress << " ..." << std::endl;

		_reactor.removeEventHandler(_socket, Poco::Observer<SessionHandlerBase, ReadableNotification>(*this, &SessionHandlerBase::OnReadable));
		// 		_reactor.removeEventHandler(_socket, Poco::Observer<SessionHandlerBase, ErrorNotification>(*this, &SessionHandlerBase::OnError));
		// 		_reactor.removeEventHandler(_socket, Poco::Observer<SessionHandlerBase, IdleNotification>(*this, &SessionHandlerBase::OnIdle));
		// 		_reactor.removeEventHandler(_socket, Poco::Observer<SessionHandlerBase, ShutdownNotification>(*this, &SessionHandlerBase::OnShutdown));
		// 		_reactor.removeEventHandler(_socket, Poco::Observer<SessionHandlerBase, TimeoutNotification>(*this, &SessionHandlerBase::OnTimeout));
		// 		_reactor.removeEventHandler(_socket, Poco::Observer<SessionHandlerBase, WritableNotification>(*this, &SessionHandlerBase::OnWritable));
	}

	bool SessionHandlerBase::Receive()
	{
		ZeroMemory(_receiveBuffer, BUFFER_SIZE);

		int n = _socket.receiveBytes(_receiveBuffer, sizeof(_receiveBuffer));
		return (n > 0);
	}

	bool SessionHandlerBase::Send(const char* message, int len)
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

	void SessionHandlerBase::Shutdown()
	{
		_socket.shutdown();
		GetServer()->OnLogout(*this);
	}
	
	void SessionHandlerBase::OnLoginSuccess(account::AccountId accountId, const std::string& token)
	{
		SetAccountId(accountId);
		_isAuthorized = true;
	}

	void SessionHandlerBase::OnLoginFailure(account::AccountId accountId, const std::string& token)
	{
		Shutdown();
	}
}