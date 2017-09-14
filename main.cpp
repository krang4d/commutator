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

using namespace std;

Scenario *CreateScenario(Subject *control_value);

int main(int argc, char *argv[])
{
    //setlocale(LC_CTYPE, "Russian");
    QApplication app(argc, argv);

    Logger *log = new AllLogger();
    //log->log("<meta http-equiv=\"refresh\" content=\"10\">");
    //QString("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>%1 %2</div>").arg("Начало работы программы").arg(log->GetDataTime());
    string msg = string("<div style='color:#00ff00; margin: 5px 0px; font-size: 20px'>") + string("Начало работы программы ") + log->GetDateTime() + string("</div>");
    log->log(msg);

    Subject *control_value = new Subject();

    mainWindow *mw = new mainWindow(control_value);
    mw->setWindowTitle(QWidget::tr("Прототип коммутатора"));
    mw->resize(1000, 500);
    mw->moveToCenter();
    mw->show();

    tools *ts = new tools(control_value, (QDialog*)mw);
    ts->setHidden(true);

    StartDialog *st = new StartDialog(mw);
    QObject::connect(st, SIGNAL(rejected()), mw, SLOT(close()));
    QObject::connect(mw, SIGNAL(tools(bool)), ts, SLOT(setHidden(bool)));
    if(st->exec() == QDialog::Accepted) {
        log->log("<div>Ф.И.О. оператора: "+st->getFIO().toStdString()+"</div>");
        log->log("<div>Номер прибора: "+st->getNumber().toStdString()+"</div>");
    }


    Scenario *sc = CreateScenario(control_value);
    control_value->setBodyPower(true);
    control_value->setDock(true);
    sc->action();
    //delete st;
    //delete mw;
    //delete control_value;
    //delete log;
    //delete sc;
    return app.exec();
}

Scenario *CreateScenario(Subject *control_value)
{
    IComposite::SPtr PowerON(new powermanager(27, control_value));
    IComposite::SPtr PowerOFF(new powermanager(0, control_value));

    IComposite::SPtr Volt(new measurement(measurement::VOLT, control_value));
    IComposite::SPtr Resist(new measurement( measurement::RESIST, control_value));

    IComposite::SPtr Y0(new mswitch(mswitch::Y0, control_value));
    IComposite::SPtr Y1(new mswitch(mswitch::Y1, control_value));

    Scenario *sc = new Scenario();
    sc->add(PowerON);
    sc->add(Volt);
    sc->add(Y0);
    sc->add(Resist);
    sc->add(Y1);
    sc->add(Volt);
    sc->add(Resist);
    sc->add(Y0);
    sc->add(PowerOFF);
    return sc;
}

