#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "logger.h"
#include "composite.h"
#include "observer.h"

class measurement : public IComposite, public Observer
{
public:

    enum operation {VOLT, RESIST};

    measurement(Logger *log, operation op, Subject *con);
    double getVoltage();
    double getResistance();

    virtual void action() override;
    virtual void update() override;

protected:
    operation op_;
    Logger *plog;
};

#endif // MEASUREMENT_H
