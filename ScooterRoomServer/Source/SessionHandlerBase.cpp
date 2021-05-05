#include "SessionHandlerBase.h"

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
}