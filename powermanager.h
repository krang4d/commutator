#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include "composite.h"
#include "observer.h"

class powermanager : public IComposite, public Observer
{
public:
    powermanager(double current_voltage, Subject *con);
    string setVoltage(double v);

    virtual string action() override;
    virtual void update() override;

protected:
    double _current_voltage;
};

#endif // POWERMANAGER_H
