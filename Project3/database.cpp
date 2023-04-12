#include "database.h"

#include <stdio.h>
#include <iostream>

Database::Database(std::string nameDb)
{
	if (sqlite3_open(nameDb.c_str(), &m_db))
	{
		fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(m_db));
	}
}

bool Database::createTable(std::string tableName, int numCols, std::string cols[])
{
	if (numCols == 0) return false;

	char* err = 0;
	std::string SQL = "CREATE TABLE IF NOT EXISTS ";
	SQL.append(tableName);
	SQL.append("(");

	for (int i = 0; i < numCols; ++i)
	{
		SQL.append(cols[i]);
		SQL.append(",");
	}

	SQL = SQL.substr(0, SQL.size() - 2);
	SQL.append(");");

	std::cout << SQL << std::endl;
	
	if (sqlite3_exec(m_db, SQL.c_str(), 0, 0, &err))
	{
		fprintf(stderr, "Ошибка SQL: %sn", err);
		sqlite3_free(err);
		sqlite3_close(m_db);
		return false;
	}

	return true;
}

bool Database::insertKey(std::string tableName, time_t time, short key)
{
	std::string SQL = "INSERT INTO " + tableName + " VALUES(";
	SQL.append(std::to_string(time));
	SQL.append(",");
	SQL.append(std::to_string(key));
	SQL.append(");");

	char* err = 0;

	std::cout << SQL << std::endl;

	if (sqlite3_exec(m_db, SQL.c_str(), 0, 0, &err))
	{
		fprintf(stderr, "Ошибка SQL: %sn", err);
		sqlite3_free(err);
		sqlite3_close(m_db);
		return false;
	}

	return true;
}