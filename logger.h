#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include "mainwindow.h"

class QFile;
class QDataTime;
using namespace std;

class Logger
{
public:
    virtual ~Logger() {}
    virtual void log(const string &str) = 0;
    QString GetDataTime();
    QString GetTime();
};

class ConsoleLogger : virtual public Logger
{
public:
    ConsoleLogger() {}
    virtual ~ConsoleLogger() {}
    void log(const string &str) override;
};

class FileLogger : virtual public Logger
{
public:
    FileLogger();
    virtual ~FileLogger();
    void log(const string &str) override;
private:
    QFile *flog;
    QTextStream *outfile;
};

class WindowLogger : virtual public Logger
{
public:
    WindowLogger(mainWindow *_mv);
    virtual ~WindowLogger() {}
    void log(const string &str) override;
protected:
    mainWindow *mw;
    vector<string> vstr;
};

class AllLogger : virtual public Logger
{
public:
    AllLogger(mainWindow *mv);
    virtual ~AllLogger();
    void log(const string &str);
protected:
    WindowLogger *wl;
    FileLogger *fl;
    ConsoleLogger *cl;
};

#endif // LOGGER_H
