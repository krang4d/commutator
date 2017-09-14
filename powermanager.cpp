#include "powermanager.h"
#include <iostream>
#include <string>

using namespace std;

powermanager::powermanager(double current_voltage) : _current_voltage(current_voltage)
{
}

string powermanager::setVoltage(double v)
{
       string str = "<span style='color:#ff0000'>Установка напряжения питания:</span>";
       return str;
}

string powermanager::action()
{
    return setVoltage(_current_voltage);
}
