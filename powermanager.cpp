#include "powermanager.h"
#include <iostream>
#include <string>

using namespace std;

powermanager::powermanager(Logger *log, double current_voltage, Subject *con) : _plog(log), _current_voltage(current_voltage), Observer(con)
{

}

void powermanager::setVoltage(double v)
{
       string str = "<div style='color:#ff0000'>Установка напряжения питания: " + to_string(v) + \
               ".   " + _plog->GetTime() + ";</div>";
       _plog->log(str);
}

void powermanager::action()
{
    setVoltage(_current_voltage);
}

void powermanager::update()
{
    setNext(getSubject()->getBodyPower() && getSubject()->getDock());
}
