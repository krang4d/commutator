#include "measurement.h"

#include <iostream>

class assert{};

using namespace std;

measurement::measurement(operation op, Subject *con)
    : op_(op), Observer(con)
{
    //log = _log;
}

string measurement::getVoltage()
{
    string str = "Измерение напряжения.";
    return str;
}

string measurement::getResistance()
{
    string str = "Измерение сопротивления.";
    return str;
}

string measurement::action()
{
    switch(op_)
    {
        case VOLT:
            return getVoltage();
        case RESIST:
            return getResistance();
        default:
            throw assert();
    }

}

void measurement::update()
{
    setNext(getSubject()->getBodyPower() && getSubject()->getDock());
}
