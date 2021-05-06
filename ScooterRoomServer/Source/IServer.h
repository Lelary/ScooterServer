#pragma once

namespace network
{
	class SessionHandlerBase;
}

namespace network
{
	struct IServer
	{
		virtual void OnLogout(SessionHandlerBase& session) = 0;
	};
}
