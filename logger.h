#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include "mainwindow.h"

using namespace std;

class Logger
{
public:
    Logger(mainWindow*_mv);
    virtual ~Logger();
    virtual void log(string &str) = 0;
    void setMessage(const string &str);
protected:
    mainWindow *mw;
    vector<string> vstr;
};

class ConsoleLogger : virtual public Logger
{
public:
    virtual ~ConsoleLogger();
    void log(string &str) override;
};

class FileLogger : virtual public Logger
{
public:
    virtual ~FileLogger();
    void log(string &str) override;
};

class WindowLogger : public Logger
{
public:
    WindowLogger(mainWindow *mv_);
    virtual ~WindowLogger();
    void log(string &str) override;
};

class AllLogger : public ConsoleLogger, FileLogger
{
public:
    virtual ~AllLogger();
    void log(string &str);
};

#endif // LOGGER_H
