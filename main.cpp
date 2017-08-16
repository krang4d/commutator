#include <iostream>

#include "mswitch.h"
#include "measurement.h"
#include "logger.h"
#include "powermanager.h"
#include "composite.h"

using namespace std;

int main(int argc, char *argv[])
{

    Logger *log(new FileLogger());

    powermanager *p(new powermanager(log, 11));
    p->setVoltage(12.5);

    Scenario s1;

    IComposite::SPtr PowerON(new powermanager(log, 27));
    IComposite::SPtr PowerOFF(new powermanager(log, 0));

    IComposite::SPtr Volt(new measurement(log, measurement::VOLT));
    IComposite::SPtr Resist(new measurement(log, measurement::RESIST));

    IComposite::SPtr Y0(new mswitch(log,mswitch::Y0));
    IComposite::SPtr Y1(new mswitch(log,mswitch::Y1));

    s1.add(PowerON);
    s1.add(Y0);
    s1.add(Volt);
    s1.add(Resist);
    s1.add(Y1);
    s1.add(Volt);
    s1.add(Resist);
    s1.add(Y0);
    s1.add(PowerOFF);

    cout << "***Выполнение сценария s1***" << endl;
    s1.action();

    delete log;

    return 0;
}
