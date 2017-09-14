#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "composite.h"

class measurement : public IComposite
{
public:

    enum operation {VOLT, RESIST};

    measurement(operation op);
    string getVoltage();
    string getResistance();

    virtual string action() override;

protected:
    operation op_;
};

#endif // MEASUREMENT_H
