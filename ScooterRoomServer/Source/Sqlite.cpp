#include "Sqlite.h"
#include <Poco/Data/SQLite/Connector.h>

namespace database
{
	void Sqlite::registerConnector()
	{
		Poco::Data::SQLite::Connector::registerConnector();
	}
}