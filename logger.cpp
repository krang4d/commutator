#include "logger.h"
#include "mainwindow.h"

class OpenFileError {};
class FileNotOpen {};
class FileOpened {};

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
    flog = new ofstream("Commutator.html");
    if (flog->is_open()) throw FileOpened();
    flog->open("Commutator.html");
    if(!flog) throw OpenFileError();
}

FileLogger::~FileLogger()
{
    flog->close();
    delete flog;
}

void FileLogger::log(const string &str)
{
//    if(flog->isOpen())
//    {
//        flog->close();
//    }

//    if(flog->exists())
//    {
//        cout << "Файл уже существует." << endl;
//    }
    //if(!flog->open(QIODevice::Append | QIODevice::Text ))
    //{
    //    cout << "Ошибка открытия log файла."<< endl;
    //}
    //outfile = new QTextStream(flog);

    //QTextCodec *codec = QTextCodec::codecForHtml("UTF-8");
    //QTextCodec::setCodecForLocale(codec);
    //outfile->setCodec(codec);
    //string *c = const_cast<string*>(&str);
    //(*outfile) << (c->c_str());
    //flog->write("\n");
    //flog->close();
    if(!flog->is_open()) throw FileNotOpen();
    (*flog) << str << "\n";
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

string Logger::GetDataTime()
{
//    QDateTime dt = QDateTime::currentDateTime();
//    return dt.toString("Время hh:mm:ss, Дата dd.MM.yyyy");
      return string("08.08.1984");
}

string Logger::GetTime()
{
//    QTime dt = QTime::currentTime();
//    return dt.toString("Время hh:mm:ss.zzz");
    std::time_t now = std::time(NULL);
    std::tm *tm = std::localtime(&now);
    constexpr int bufsize = 100;
    char buf[bufsize];
    if(std::strftime(buf, bufsize, "Врем %T", tm) != 0)
    {
        double now = (int)(difftime(clock(), start_t)) % int(CLOCKS_PER_SEC);

        return (buf + string(".") + std::to_string((int)now));// + string(" CLOCKS_PER_SEC = ") + std::to_string(int(CLOCKS_PER_SEC)));
    }
}
