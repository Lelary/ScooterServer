#pragma once
#pragma once

#include <Poco/Data/Session.h>
#include <vector>
#include <iostream>

namespace database
{
	using namespace Poco::Data::Keywords;

	class RdbSession
	{
	public:
		RdbSession(const std::string& dbName);

	protected:
		Poco::Data::Statement CreateStatement();
		Poco::Data::Session _session;
		const bool _async = true;
	};
	//InvalidAccessException
}