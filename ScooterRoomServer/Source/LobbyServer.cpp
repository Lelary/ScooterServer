#include "LobbyServer.h"

namespace local
{
	bool AuthorizeAccount(account::AccountId accountId, const std::string& token)
	{
		if (accountId == 0)
			return false;

		return true;
	}
}

namespace network
{
	LobbyServer::LobbyServer(Port port)
		:Server(port), _packetHandler(*this)
	{
	}

	bool LobbyServer::TryLogin(account::AccountId accountId, LobbySessionHandler& session, const std::string& token)
	{
		if (session.IsAuthorized())
			return false;

		auto foundSession = _sessions.find(accountId);
		if (foundSession != _sessions.end())
		{
			foundSession->second.Shutdown();
			return false;
		}

		if (!local::AuthorizeAccount(accountId, token))
		{
			return false;
		}

		_sessions.emplace(accountId, session);
		return true;
	}

	void LobbyServer::OnLogout(SessionHandlerBase& session)
	{
		if (session.IsAuthorized())
		{
			_sessions.erase(session.GetAccountId());
		}
	}

	bool LobbyServer::HandlePacket(LobbySessionHandler& session, const char* buffer)
	{
		auto packet = _packetParser.Parse(buffer);
		if (packet == nullptr)
			return false;

		if (!session.IsAuthorized())
		{
			if (packet->packetType != packet::to_lobby::PacketType::ReqLogin)
			{
				session.Shutdown();
				return false;
			}
		}

		if (!_packetHandler.Handle(session, std::move(packet)))
			return false;

		return true;
	}
}