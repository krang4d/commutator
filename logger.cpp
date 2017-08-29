#include "logger.h"
#include <iostream>
#include <QString>

void ConsoleLogger::log(const string &str)
{
    cout << "ConsoleLogger: " << str << endl;
}

void FileLogger::log(const string &str)
{
    cout << "FileLogger: " << str << endl;
}

WindowLogger::WindowLogger(mainWindow *_mv) :  mw(_mv), vstr(0)
{

}

void WindowLogger::log(const string &str)
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



AllLogger::AllLogger(mainWindow *mv)
{
    fl = new FileLogger();
    cl = new ConsoleLogger();
    wl = new WindowLogger(mv);
}

AllLogger::~AllLogger()
{
    delete fl;
    delete cl;
    delete wl;
}

void AllLogger::log(const string &str)
{
    fl->log(str);
    cl->log(str);
    wl->log(str);
}
