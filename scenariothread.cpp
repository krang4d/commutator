#include "scenariothread.h"

ScenarioThread::ScenarioThread()
{
    sc = new Scenario();
    sc->setNext(true);
}

ScenarioThread::~ScenarioThread()
{
    delete sc;
}

void ScenarioThread::run(){
    IComposite::SPtr PowerON(new powermanager(27));
    IComposite::SPtr PowerOFF(new powermanager(0));

    IComposite::SPtr Volt(new measurement(measurement::VOLT));
    IComposite::SPtr Resist(new measurement( measurement::RESIST));

    IComposite::SPtr Y0(new mswitch(mswitch::Y0));
    IComposite::SPtr Y1(new mswitch(mswitch::Y1));

    sc->add(PowerON);
    sc->add(Volt);
    sc->add(Y0);
    sc->add(Resist);
    sc->add(Y1);
    sc->add(Volt);
    sc->add(Resist);
    sc->add(Y0);
    sc->add(PowerOFF);

    connect(sc, SIGNAL(newmessage(QString)), SIGNAL(threadmessage(QString)));
    sc->action();
}
