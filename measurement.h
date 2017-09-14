#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "composite.h"
#include "observer.h"

class measurement : public IComposite, public Observer
{
public:

    enum operation {VOLT, RESIST};

    measurement(operation op, Subject *con);
    string getVoltage();
    string getResistance();

    virtual string action() override;
    virtual void update() override;

protected:
    operation op_;
};

#endif // MEASUREMENT_H
