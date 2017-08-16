#include "measurement.h"

#include <iostream>

class assert{};

using namespace std;

measurement::measurement(Logger *log, operation op)
    : _plog(log), _op(op)
{
    //log = _log;
}

double measurement::getVoltage()
{
    string str = "Измерение напряжения";
    _plog->log(str);
    return 0;
}

double measurement::getResistance()
{
    string str = "Измерение сопротивленияя";
    _plog->log(str);
    return 0;
}

void measurement::action()
{
    switch(_op)
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
