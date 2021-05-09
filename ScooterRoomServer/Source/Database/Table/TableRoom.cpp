#include "TableRoom.h"

namespace database
{
	namespace table 
	{
		using namespace Poco::Data::Keywords;
		using Poco::Data::Session;
		using Poco::Data::Statement;

		TableRoom::TableRoom()
			:RdbSession("room.db")
		{
		}

		void TableRoom::CreateTable()
		{
			_session << "DROP TABLE IF EXISTS Room", now;
			_session << "CREATE TABLE Room (id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(30), start INTEGER)", now;
		}

		void TableRoom::Insert(std::string name)
		{
			int start = 0;

			auto statement = CreateStatement();
			statement << "INSERT INTO Room (name, start) VALUES (?, ?)",
				use(name),
				use(start);

			statement.execute();
			statement.wait();
		}

		void TableRoom::Select()
		{
			auto statement = CreateStatement();

			Model model;

			statement << "SELECT id, name, start FROM Room",
				into(model.id),
				into(model.name),
				into(model.start),
				range(0, 1);

			while (!statement.done())
			{
				statement.execute();
				statement.wait();
				std::cout << model.id << " " << model.name << " " << model.start << std::endl;
			}
		}
	}
}

