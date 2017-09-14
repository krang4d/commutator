#include "measurement.h"

#include <iostream>

class assert{};

using namespace std;

measurement::measurement(operation op)
    : op_(op)
{

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
            return 0;
    }

}
