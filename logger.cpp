#include "logger.h"
#include "mainwindow.h"

class CannotOpenFile {};
class FileNotOpen {};

Logger::Logger()
{
    start_t = clock();
}
void ConsoleLogger::log(const string &str)
{
    cout << str << endl;
}

FileLogger::FileLogger()
{
    flog = new ofstream();
}

FileLogger::~FileLogger()
{
    delete flog;
}

void FileLogger::log(const string &str)
{
//string *c = const_cast<string*>(&str);

    flog->open("Commutator.html",ios_base::ate | ios_base::app);
    if(!flog) throw CannotOpenFile();
    //if(!flog->is_open()) throw FileNotOpen();
    flog->write(str.c_str(), str.size());
    flog->close();
}

WindowLogger::WindowLogger(mainWindow *_mv) :  mw(_mv), vstr(0)
{

}

void WindowLogger::log(const string &str)
{
    vstr.push_back(str);
    string winstr;
    for(uint i = 0; i < vstr.size(); i++)
    {
        winstr += vstr[i];
        winstr += '\n';
    }
    mw->setNextLine(winstr);
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

string Logger::GetDateTime() const
{
    std::time_t now = std::time(NULL);
    std::tm *tm = std::localtime(&now);
    constexpr int bufsize = 100;
    char buf[bufsize];
    if(std::strftime(buf, bufsize, "Дата %d.%m.%Y Врем %T", tm) != 0)
    {
        return buf;
    }
    return string("Error: GetDateTime()");
}

string Logger::GetTime()
{
    std::time_t now = std::time(NULL);
    std::tm *tm = std::localtime(&now);
    constexpr int bufsize = 100;
    char buf[bufsize];
    if(std::strftime(buf, bufsize, "Врем %T", tm) != 0)
    {
        double now = (int)(difftime(clock(), start_t)) % int(CLOCKS_PER_SEC);
        return (buf + string(".") + std::to_string((int)now)); // + string(" CLOCKS_PER_SEC = ") + std::to_string(int(CLOCKS_PER_SEC)));
    }
    delete tm;
    return string("Error: LoggerGetTime()");
}
