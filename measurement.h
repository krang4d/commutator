#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "logger.h"
#include "composite.h"

class measurement : public IComposite
{
public:

    enum operation {VOLT, RESIST};

    measurement(Logger *log, operation op);
    double getVoltage();
    double getResistance();

    virtual void action() override;

protected:
    Logger *_plog;
    operation _op;

};

#endif // MEASUREMENT_H
