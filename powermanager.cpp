#include "powermanager.h"
#include <iostream>
#include <string>

using namespace std;

powermanager::powermanager(double current_voltage, Subject *con) : _current_voltage(current_voltage), Observer(con)
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

void powermanager::update()
{
    setNext(getSubject()->getBodyPower() && getSubject()->getDock());
}
