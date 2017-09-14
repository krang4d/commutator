#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include "composite.h"

class powermanager : public IComposite
{
public:
    powermanager(double current_voltage);
    string setVoltage(double v);

    virtual string action() override;
protected:
    double _current_voltage;
};

#endif // POWERMANAGER_H
