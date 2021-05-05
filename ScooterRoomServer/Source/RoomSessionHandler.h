#pragma once
#include "SessionHandlerBase.h"

namespace network
{
	class RoomSessionHandler : public SessionHandlerBase
	{
	public:
		RoomSessionHandler(StreamSocket& socket, SocketReactor& reactor);
		virtual void OnReadable(ReadableNotification* pNotification) override;
	private:
		bool _OnReadable(ReadableNotification* pNotification);
	};
}