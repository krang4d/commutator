﻿#include <iostream>
#include <QApplication>

#include "mainwindow.h"
#include "startdialog.h"
#include "logger.h"
#include "mswitch.h"
#include "measurement.h"
#include "powermanager.h"
#include "observer.h"
#include "tools.h"
#include <QThread>
#include <scenariothread.h>

using namespace std;

class threadClass;
Scenario *CreateScenario();
void threadFunction(int &a);

int main(int argc, char *argv[])
{
    //setlocale(LC_CTYPE, "Russian");
    QApplication app(argc, argv);

    Subject *control_value = new Subject();
    Logger *log = new AllLogger();

    control_value->setBodyPower(true);
    control_value->setDock(true);

    mainWindow *mw = new mainWindow(control_value);
    mw->setWindowTitle(QWidget::tr("Прототип коммутатора"));
    mw->resize(1000, 500);
    mw->moveToCenter();
    mw->show();


    //log->log("<meta http-equiv=\"refresh\" content=\"10\">");
    //QString("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>%1 %2</div>").arg("Начало работы программы").arg(log->GetDataTime());
    string msg = string("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>") + string("Начало работы программы ") + log->GetDateTime() + string("</div>");
    log->log(msg);
    mw->setNextLine(msg);

    tools *ts = new tools(control_value, (QDialog*)mw);
    ts->setHidden(true);

    StartDialog *st = new StartDialog(mw);
    QObject::connect(st, SIGNAL(rejected()), mw, SLOT(close()));
    QObject::connect(mw, SIGNAL(tools(bool)), ts, SLOT(setHidden(bool)));
    if(st->exec() == QDialog::Accepted) {
        string msg("<div>Ф.И.О. оператора: "+st->getFIO().toStdString()+"</div>");
        log->log(msg);
        mw->setNextLine(msg);
        msg = "<div>Номер прибора: "+st->getNumber().toStdString()+"</div>";
        log->log(msg);
        mw->setNextLine(msg);
    }

    ScenarioThread thread1;
    QObject::connect(&thread1, SIGNAL(threadmessage(QString)), mw, SLOT(setmessage(QString)));
    //ScenarioThread thread2;
    thread1.start();
    //thread2.start();

//    std::thread thr(threadFunction, std::ref(control_value), std::ref(log));
//    thr.join();


    //sc->action();
    //function<void()>f = bind(&Scenario::action, sc);

    //std::thread *thr = new std::thread(bind(&Scenario::action, sc));
    //thr->join();

    //sc->action();
    //mw->setNextLine(msg);
    //delete st;
    //delete mw;
    //delete control_value;
    //delete log;
    //delete sc;
    return app.exec();
}
