#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

class mainWindow;

using namespace std;

class Logger
{
public:
    Logger();
    virtual ~Logger() {}
    virtual void log(const string &str) = 0;
    string GetDateTime() const;
    string GetTime();
private:
    clock_t start_t;
};

class ConsoleLogger : virtual public Logger
{
public:
    ConsoleLogger() {}
    virtual ~ConsoleLogger() {}
    virtual void log(const string &str) override;
};

class FileLogger : virtual public Logger
{
public:
    FileLogger();
    virtual ~FileLogger();
    virtual void log(const string &str) override;
private:
    ofstream *flog;
};

class WindowLogger : virtual public Logger
{
public:
    explicit WindowLogger(mainWindow *_mv);
    virtual ~WindowLogger() {}
    virtual void log(const string &str) override;
protected:
    mainWindow *mw;
    vector<string> vstr;
};

class AllLogger : virtual public Logger
{
public:
    explicit AllLogger(mainWindow *mv);
    virtual ~AllLogger();
    virtual void log(const string &str);
protected:
    WindowLogger *wl;
    FileLogger *fl;
    ConsoleLogger *cl;
};

#endif // LOGGER_H
