#include "FromLobbyPacketWriter.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include "PacketGroup.h"
#include "LobbyPacket.h"

namespace packet
{
	using namespace Poco;
	using namespace Poco::JSON;
	using namespace Poco::Dynamic;
	using namespace from_lobby;

	std::string FromLobbyPacketWriter::Write(const FromLobbyPacket& packet)
	{
		DynamicStruct json;
		packet.Write(json);

		Stringifier sf;
		std::stringstream ss;
		sf.condense(json, ss);

		return ss.str();
	}
}