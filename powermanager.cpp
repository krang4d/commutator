#include "powermanager.h"
#include <iostream>
#include <string>

using namespace std;

powermanager::powermanager(Logger *log, double current_voltage) : _plog(log), _current_voltage(current_voltage)
{

}

void powermanager::setVoltage(double v)
{
       string str = "Установка напряжения питания:" + to_string(v);
       _plog->log(str);
}

void powermanager::action()
{
    setVoltage(_current_voltage);
}
