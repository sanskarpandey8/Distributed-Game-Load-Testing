#include "../include/Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

string Logger::getCurrentTime()
{
    auto now = chrono::system_clock::now();

    time_t current = chrono::system_clock::to_time_t(now);

    tm local = *localtime(&current);

    char buffer[20];

    strftime(buffer,
             sizeof(buffer),
             "%H:%M:%S",
             &local);

    return string(buffer);
}

void Logger::info(const string& message)
{
    cout << "[" << getCurrentTime() << "] "
         << "[INFO] "
         << message
         << endl;
}

void Logger::warning(const string& message)
{
    cout << "[" << getCurrentTime() << "] "
         << "[WARNING] "
         << message
         << endl;
}

void Logger::error(const string& message)
{
    cout << "[" << getCurrentTime() << "] "
         << "[ERROR] "
         << message
         << endl;
}