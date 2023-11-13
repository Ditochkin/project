#include "sqlite3.h"
#include <string>

class Database
{
private:
	sqlite3* m_db;

public:

	bool createDatabase(std::string nameDb);

	bool createTable(std::string tableName, int numCols, std::string cols[]);

	bool insertMouseKey(std::string tableName, time_t time, short key);

	bool insertKeyboardKey(std::string tableName, time_t time, short key, bool pressed);

	bool clear(std::string tableName);
};