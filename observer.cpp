#include "observer.h"

void Subject::attach(Observer *obs)
{
    views.push_back(obs);
}

void Subject::setBodyPower(bool bp)
{
    BodyPower = bp;
    notify();
}

void Subject::setDock(bool d)
{
    Dock = d;
    notify();
}

bool Subject::getBodyPower()
{
    return BodyPower;
}

bool Subject::getDock()
{
    return Dock;
}

void Subject::notify()
{
    for(unsigned int i=0; i < views.size(); i++)
        views[i]->update();
}

Observer::Observer(Subject *con) : control(con)
{
    control->attach(this);
}

Subject *Observer::getSubject()
{
    return control;
}

