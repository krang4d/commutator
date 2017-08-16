#include "logger.h"

#include <iostream>

Logger::~Logger()
{

}

ConsoleLogger::~ConsoleLogger()
{

}

void ConsoleLogger::log(string &str)
{
    cout << "ConsoleLogger: " << str << endl;
}

FileLogger::~FileLogger()
{

}

void FileLogger::log(string &str)
{
    cout << "FileLogger: " << str << endl;
}

AllLogger::~AllLogger()
{

}

void AllLogger::log(string &str)
{
    ConsoleLogger::log(str);
    FileLogger::log(str);
}
