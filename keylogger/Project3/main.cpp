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
	
	db.createDatabase("data.sqlite3");	

	std::string keyboardCols[3] = { "time", "key", "pressing" };
	db.createTable("keyboard", 3, keyboardCols);
	db.clear("keyboard");

	std::string mouseCols[2] = { "time, key" };
	db.createTable("mouse", 2, mouseCols);
	db.clear("mouse");

	MouseHook mouseHook;
	mouseHook.start(db);

	Keylogger keylogger;
	keylogger.start(db);

	return 0;
}