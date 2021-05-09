#include "RdbSession.h"
#include <string>
#include <Poco/Data/Session.h>

namespace database
{
	RdbSession::RdbSession(const std::string& dbName)
		:_session("SQLite", dbName)
	{
	}

	Poco::Data::Statement RdbSession::CreateStatement()
	{
		Poco::Data::Statement statement(_session);
		statement.setAsync(_async);
		return statement;
	}
}