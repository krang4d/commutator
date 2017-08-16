#ifndef LOGGER_H
#define LOGGER_H

#include <string>
using namespace std;

class Logger
{
public:
    virtual ~Logger();
    virtual void log(string &str) = 0;
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

class AllLogger : public ConsoleLogger, FileLogger
{
public:
    virtual ~AllLogger();
    void log(string &str);
};

#endif // LOGGER_H
