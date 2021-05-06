#pragma once
#include "IServer.h"
#include "SessionHandlerBase.h"
#include "ScooterSocketAcceptor.h"

namespace network
{
	using namespace Poco::Net;
	using Port = Poco::UInt16;
	constexpr Port PORT_NONE = 0;

	template <typename T>
	class Server : public IServer
	{
	public:
		Server(Port port)
			:_port(port)
		{
		}

		bool Initialize()
		{
			if (_acceptor != nullptr)
				return false;

			try
			{
				ServerSocket serverSocket(_port);
				//_reactor.setTimeout(Poco::Timespan(10, 0));
				_acceptor = std::make_unique<ScooterSocketAcceptor<T>>(*this, serverSocket, _reactor);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				return false;
			}

			return true;
		}

		void Run()
		{
			try
			{
				_reactor.run();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
		}

		inline Port GetPort() const { return _port; }

	private:
		const Port _port;
		SocketReactor _reactor;
		std::unique_ptr<ScooterSocketAcceptor<T>> _acceptor;
	};
}