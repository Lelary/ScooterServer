#pragma once
#include "../../RdbSession.h"

namespace database
{
	namespace table
	{
		class TableRoom : database::RdbSession
		{
		public:
			struct Model
			{
				int id = 0;
				std::string name;
				bool start = false;
			};

		public:
			TableRoom();
			void CreateTable();
			void Insert(std::string name);
			void Select();
		};
	}
}