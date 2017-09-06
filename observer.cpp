﻿#include "observer.h"

Subject::Subject(Logger *log) : plog(log)
{

}

void Subject::attach(Observer *obs)
{
    views.push_back(obs);
}

void Subject::setBodyPower(bool bp)
{
    BodyPower = bp;
    if(!bp) plog->log("<div>Крпус <span style='color:#ff0000;'>БРАК </span>" + plog->GetTime() + "</div>");
    notify();
}

void Subject::setDock(bool d)
{
    Dock = d;
    if(!d) plog->log("<div>Стыковка <span style='color:#ff0000;'>БРАК </span>" + plog->GetTime() + "</div>");
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

