#include "sqlite3.h"
#include <string>

class Database
{
private:
	sqlite3* m_db;

public:
	Database(std::string nameDb);

	bool createTable(std::string tableName, int numCols, std::string cols[]);

	bool insertKey(std::string tableName, time_t time, short key);
};