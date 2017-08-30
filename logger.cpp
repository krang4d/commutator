#include "logger.h"
#include <iostream>

void ConsoleLogger::log(const string &str)
{
    cout << "ConsoleLogger: " << str << endl;
}

FileLogger::FileLogger()
{
    flog = new QFile("Commutator.html");
}

FileLogger::~FileLogger()
{
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
    if(!flog->open(QIODevice::Append | QIODevice::Text ))
    {
        cout << "Ошибка открытия log файла."<< endl;
    }
    outfile = new QTextStream(flog);

    QTextCodec *codec = QTextCodec::codecForHtml("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    outfile->setCodec(codec);
    string *c = const_cast<string*>(&str);
    (*outfile) << (c->c_str());
    flog->write("\n");
    flog->close();
}

WindowLogger::WindowLogger(mainWindow *_mv) :  mw(_mv), vstr(0)
{

}

void WindowLogger::log(const string &str)
{
    //QString qstr(str.c_str());
    vstr.push_back(str);
    QString qstr;
    for(uint i = 0; i < vstr.size(); i++)
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

QString Logger::GetDataTime()
{
    QDateTime dt = QDateTime::currentDateTime();
    return dt.toString();
}
