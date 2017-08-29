#include "logger.h"
#include <iostream>
#include <QString>

Logger::Logger(mainWindow *_mv): mw(_mv), vstr(0)
{

}

Logger::~Logger()
{

}

void Logger::setMessage(const string &str)
{
    vstr.push_back(str);
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

WindowLogger::WindowLogger(mainWindow *mv_) : Logger(mv_)
{

}

WindowLogger::~WindowLogger()
{

}

void WindowLogger::log(string &str)
{
    //QString qstr(str.c_str());
    vstr.push_back(str);
    QString qstr;
    for(int i = 0; i < vstr.size(); i++)
    {
        string a = vstr[i];
        qstr += a.c_str();
        qstr += '\n';
    }
    mw->setNextLine(&qstr);
}
