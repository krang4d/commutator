#include "measurement.h"

#include <iostream>

class assert{};

using namespace std;

measurement::measurement(Logger *log, operation op, Subject *con)
    : plog(log), op_(op), Observer(con)
{
    //log = _log;
}

double measurement::getVoltage()
{
    string str = "<div>Измерение напряжения.   " + plog->GetTime() + ";</div>";
    plog->log(str);
    return 0;
}

double measurement::getResistance()
{
    string str = "<div>Измерение сопротивления.   " + plog->GetTime() + "</div>";
    plog->log(str);
    return 0;
}

void measurement::action()
{
    switch(op_)
    {
        case VOLT:
            getVoltage();
            break;
        case RESIST:
            getResistance();
            break;
        default:
            throw assert();
    }

}

void measurement::update()
{
    setNext(getSubject()->getBodyPower() && getSubject()->getDock());
}
