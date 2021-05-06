#pragma once

namespace network
{
	template <typename ServiceHandler>
	class ScooterSocketAcceptor : public Poco::Net::SocketAcceptor<ServiceHandler>
	{
	public:
		ScooterSocketAcceptor(IServer& server, ServerSocket& socket, SocketReactor& reactor)
			:SocketAcceptor<ServiceHandler>(socket, reactor), _server(server)
		{

		}

	protected:
		virtual ServiceHandler* createServiceHandler(StreamSocket& socket) override
		{
			auto session = Poco::Net::SocketAcceptor<ServiceHandler>::createServiceHandler(socket);
			session->SetServer(&_server);
			return session;
		}

	private:
		IServer& _server;
	};
}
