#include "scenariothread.h"

ScenarioThread::ScenarioThread()
{   
}

ScenarioThread::~ScenarioThread()
{
}

void ScenarioThread::run(){
    Scenario *sc = new Scenario();
    sc->setNext(true);
    connect(sc, SIGNAL(newmessage(QString)), SIGNAL(threadmessage(QString)));

    IComposite::SPtr PowerON(new powermanager(27));
    IComposite::SPtr PowerOFF(new powermanager(0));

    IComposite::SPtr Volt(new measurement(measurement::VOLT));
    IComposite::SPtr Resist(new measurement( measurement::RESIST));

    IComposite::SPtr Y0(new mswitch(mswitch::Y0));
    IComposite::SPtr Y1(new mswitch(mswitch::Y1));
    IComposite::SPtr Y2(new mswitch(mswitch::Y2));

    sc->add(PowerON);
    sc->add(Volt);
    sc->add(Y0);
    sc->add(Resist);
    sc->add(Y1);
    sc->add(Volt);
    sc->add(Resist);
    sc->add(Y2);
    sc->add(PowerOFF);
    sc->action();
    delete sc;
}
